# GitHub Guidelines

Clone the main branch on your dev machine. Instructions are on GitHub.

The `main` branch of your repository is protected. You will not be able to push directly to this branch.

There are `git` tools built into Visual Studio (IDE), but some students prefer the command-line interface (CLI). In either case, understanding the CLI will help you understand the correct workflow.

There are multiple organization strategies employed by game studios, but I want you to use the following strategy.  It doesn't backfire and is simple.

### To update your local copy of `main` from the CLI

```
git pull origin main
```

You do NOT do your work on `main` but instead...

### Make a working branch

```
git checkout -b user/eric/myfeature1
```

 - The `checkout` command switches to the named branch and the `-b` option creates a new branch. The new branch is created from the current branch.
 - of course, replace `eric` with your name
 - and replace `myfeature1` with a short name describing the work
 - You should create a new branch for every feature or change you work on. This may seem onerous, but it will save you time in the future and help prevent loss of work.

#### Note: To switch between branches

```
git checkout user/eric/myfeature1
```

### Workflow

__*This is easiest in the IDE*__ but here are the CLI steps.


#### Staging your changes

Changes are not automatically added to your branch. You need to stage them first.
```
// to stage a file or files
git add path-to-file(s)

// to add all your changes
git add *

```

#### Committing your changes
```
git commit -m "describe the change here, this will become the title of your code-review"
```

#### Pushing your changes to the remote server
```
git push origin user/eric/myfeature1
```

This creates a temporary remote branch called `user/eric/myfeature1`

#### Completing the process
- On GitHub, select the `Pull Requests` tab
- Provided you are authenticated correctly, the UI will prompt you to create a PR from `user/eric/myfeature1`
- Add a description and create the PR
- Then, one or more of your teammates should review the code
    - the process is iterative
    - if you need to make changes, change your local files, stage and commit them. Then push again to the remote server
    - the PR will automatically be updated
- Once you have an approval and you're fairly certain you're not going to break other devs, you want to **Squash and Merge** your changes
    - squashing compresses all of your commits into a single commit before merging into `main`
    - this makes it easier to undo bad merges, and keeps the `main` branch cleaner

Your temporary remote branch should be deleted automatically when you merge your PR.

### Please do not use other branching strategies
In the past, some teams have insisted on working from a feature branch and then periodically merging things into main. I'll explain in class why this approach is sub-optimal.
