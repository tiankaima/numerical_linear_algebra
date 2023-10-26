* [x] Checkout to new branch, namely `vs-release/1.0.0`
* Run on Windows machine
  [`cmake -G "Visual Studio 17 2022" -A x64`](https://github.com/tiankaima/numerical_algebra/pull/1/commits/d2bf0bae08e456c0ca880c22dfdaed79e9cf2608)
* [ ] Commit, message: 
  `chore: cmake -G "Visual Studio 17 2022" -A x64`
* Manually replace 
  `$(SolutionDir)\` 
  with
  `$(SolutionDir)`
* [ ] Commit, message:
  `chore: replace path`
* [ ] Then try to open the `.sln` file on Windows, build it and run the program.
* If works, you still need to `git reset  --hard HEAD` to restore any change Visual Studio made during build process.
* [ ] Then pack the whole thing to zip and send as homework. 
  *ignoring `.vs` files might be troublesome, try downloading from GitHub*
