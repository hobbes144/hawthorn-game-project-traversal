#include <array>
#include <cmath>
#include <stdexcept>

template <typename T, size_t N>
class VectorTemplated {
private:
    std::array<T, N> data;

public:
    VectorTemplated() : data{} {}
    explicit VectorTemplated(const std::array<T, N>& values) : data(values) {}

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    // Formula: [v1 + u1, v2 + u2, ..., vn + un]
    VectorTemplated operator+(const VectorTemplated& other) const {
        VectorTemplated result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] + other[i];
        }
        return result;
    }

    // Formula: [v1 - u1, v2 - u2, ..., vn - un]
    VectorTemplated operator-(const VectorTemplated& other) const {
        VectorTemplated result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] - other[i];
        }
        return result;
    }

    // Formula: [v1 * s, v2 * s, ..., vn * s]
    VectorTemplated operator*(T scalar) const {
        VectorTemplated result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] * scalar;
        }
        return result;
    }

    // Formula: v1*u1 + v2*u2 + ... + vn*un
    T dot(const VectorTemplated& other) const {
        T result = 0;
        for (size_t i = 0; i < N; ++i) {
            result += data[i] * other[i];
        }
        return result;
    }

    T magnitudeSquared() const {
        return dot(*this);
    }

    // Formula: sqrt(v1^2 + v2^2 + ... + vn^2)
    T magnitude() const {
        return std::sqrt(dot(*this));
    }

    // Formula: v / |v|, where |v| is the magnitude
    VectorTemplated normalized() const {
        T mag = magnitude();
        if (mag == 0) {
            throw std::runtime_error("Cannot normalize zero vector");
        }
        return *this * (1 / mag);
    }

    // Specific to 3D vectors
    // Formula: [v2*u3 - v3*u2, v3*u1 - v1*u3, v1*u2 - v2*u1]
    VectorTemplated cross(const VectorTemplated& other) const {
        static_assert(N == 3, "Cross product is only defined for 3D vectors");
        return VectorTemplated({
            data[1] * other[2] - data[2] * other[1],
            data[2] * other[0] - data[0] * other[2],
            data[0] * other[1] - data[1] * other[0]
            });
    }
};