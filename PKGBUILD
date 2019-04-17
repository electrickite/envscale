pkgname=envscale
pkgver=0.1.0
pkgrel=1
pkgdesc="Wrapper that adds scale factor environment variables"
arch=("any")
license=("MIT")
depends=("gtk3")
source=("envscale.c" "Makefile")
sha1sums=("SKIP" "SKIP")

package() {
  cd "${srcdir}"
  make PREFIX=/usr DESTDIR="${pkgdir}" install
}
