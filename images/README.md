# Images
This directory stores the images that are used throughout the project. Upon
download it should be empty, with the exception of this README.md file. This is
to prevent using up space on the GitHub repository, and prevent git from keeping
track of changes to the images themselves. All of the figures are made from code
contained in this repository (asymptote, tikz, and the C programming language
are the only tools used). There are shell scripts at the top-level of this
repository for creating the necessary images and dumping them into this folder.

## Linux Users
Both `pdf2svg` and `inkscape` are used to run the shell script. These can be
installed with `apt-get` or whatever package manager your distribution uses.
```Bash
    sudo apt-get install pdf2svg
    sudo apt-get install inkscape
```
Next, at the top-level run the install script. If you need to add permissions,
you may do so as follows:
```Bash
    chmod +x make_figs_linux.sh
```
Then run the script.
```Bash
    ./make_figs_linux.sh
```

## MacOS Users
The `ImageMagick` software is used in the install script and this comes
installed on MacOS (standard for High Sierra, Mojave, and Catalina). Simply run
the setup script. If you need to add permissions, do so as follows:
```Bash
    chmod +x make_figs_macos.sh
```
Then run the script.
```Bash
    ./make_figs_macos.sh
```

## Notes for Both
It should take a while to run since there are quite a lot of figures. You will
need asymptote (which comes installed with tex-live and most other latex
distributions) as well as the C compiler `gcc` to successfully run this. Linux
users can install this with `apt-get`, mac users will need to install `xcode`
which is Apple's developer toolkit.