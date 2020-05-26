# Images
This directory stores the images that are used throughout the project. Upon
download it should be empty, with the exception of this README.md file. This is
to prevent using up space on the GitHub repository, and prevent git from keeping
track of changes to the images themselves. All of the figures are made from code
contained in this repository (asymptote, tikz, and the C programming language
are the only tools used). There are shell scripts at the top-level of this
repository for creating the necessary images and dumping them into this folder.

## Linux Users
`ImageMagick` is needed to installation. This can be installed via `apt-get` or
whatever package manager your distribution uses (`apt-get` is standard for
Debian and Debian-based distrobutions like Ubuntu).
```Bash
    sudo apt-get install imagemagick
```
Once this is successfully installed return to the main setup instructions found
in the READMA.

## MacOS Users
The `ImageMagick` software is used in the install script and this comes
installed on MacOS (standard for High Sierra, Mojave, and Catalina). Simply run
the setup script. If for some reason you do not have `ImageMagick` installed,
navigate to the download page and follow the setup:
[https://imagemagick.org/script/download.php](https://imagemagick.org/script/download.php)


## Notes for Both
It should take a while to run since there are quite a lot of figures. You will
need asymptote (which comes installed with tex-live and most other latex
distributions) as well as the C compiler `gcc` to successfully run this. Linux
users can install this with `apt-get` (or whatever package manager they use),
mac users will need to install `xcode` which is Apple's developer toolkit.