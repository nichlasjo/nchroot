# nchroot
* Namespace chrooter for linux.

## Prereqs:

* Musl-gcc toolchain is the way to go.
* nchroot relies on Linux syscalls.
* chrootdir with /proc present.

## Usage:
* compile and copy binary to your favorite $PATH
* nchroot /my/chroot/directory [ /bin/command ]

## About:
* nchroot defaults to sh if no command is given.
* Im aiming for minimalism and having fun.

## Note:
*Im just a pleb and nchroot should be viewed from that angle.*
