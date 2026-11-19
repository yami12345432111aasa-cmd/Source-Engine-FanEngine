# Fan Engine Editor — GitHub Actions starter

This repository contains a small Qt 6 / C++17 editor starter and a GitHub Actions workflow.

## What happens on GitHub

When you push to `main` or `master`, open a pull request, or run the workflow manually:

1. GitHub checks out the repository.
2. The hosted runner installs Qt and build dependencies.
3. CMake configures the project.
4. Ninja compiles the editor.
5. GitHub stores the resulting executable as a downloadable workflow artifact.

## How to use

1. Create a GitHub repository.
2. Upload the contents of this ZIP to the repository root.
3. Commit and push to `main` (or `master`).
4. Open the **Actions** tab in GitHub.
5. Open the latest **Build Fan Engine Editor** run.
6. Download `FanEngine-Editor-Windows` or `FanEngine-Editor-Linux` from **Artifacts**.

## Important

The YAML file is a GitHub Actions workflow, not a local build script. GitHub runs it on its own hosted PC/VM runners.

This starter builds the PC editor only. Selecting PS3 in the future will require a separate PS3 cross-compilation job, a compatible PPU/SPU toolchain, and the appropriate SDK/libraries. A normal GitHub Windows/Linux runner cannot magically produce a valid PS3 build without those tools being installed and configured.
