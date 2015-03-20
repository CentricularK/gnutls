SMP=-j4

GNUTLS_VERSION:=3.2.15
GNUTLS_FILE:=gnutls-$(GNUTLS_VERSION).tar.xz
GNUTLS_DIR:=gnutls-$(GNUTLS_VERSION)

GMP_VERSION=6.0.0
GMP_VERSIONA=6.0.0a
GMP_FILE:=gmp-$(GMP_VERSIONA).tar.bz2
GMP_SERV_DIR:=gmp-$(GMP_VERSIONA)
GMP_DIR:=gmp-$(GMP_VERSION)

P11_KIT_VERSION=0.20.2
P11_KIT_FILE:=p11-kit-$(P11_KIT_VERSION).tar.gz
P11_KIT_DIR:=p11-kit-$(P11_KIT_VERSION)

NETTLE_VERSION=2.7.1
NETTLE_FILE:=nettle-$(NETTLE_VERSION).tar.gz
NETTLE_DIR:=nettle-$(NETTLE_VERSION)

PKG_CONFIG_DIR:=$(PWD)/win32/lib/pkgconfig/
CROSS_DIR:=$(PWD)/win32
BIN_DIR:=$(CROSS_DIR)/bin
LIB_DIR:=$(CROSS_DIR)/lib
HEADERS_DIR:=$(CROSS_DIR)/include
DEVCPP_DIR:=$(PWD)/devcpp
LDFLAGS=
#doesn't seem to work
#LDFLAGS=-static-libgcc

all: update-gpg-keys gnutls-w32

upload: gnutls-w32 devpak
	../build-aux/gnupload --to ftp.gnu.org:gnutls/w32 $(GNUTLS_DIR)-w32.zip
	../build-aux/gnupload --to ftp.gnu.org:gnutls/w32 gnutls-$(GNUTLS_VERSION)-1gn.DevPak

update-gpg-keys:
	gpg --recv-keys 96865171 B565716F D92765AF A8F4C2FD DB899F46

$(GNUTLS_DIR)-w32.zip: $(LIB_DIR) $(BIN_DIR) $(GNUTLS_DIR)/.installed
	rm -rf $(CROSS_DIR)/etc $(CROSS_DIR)/share $(CROSS_DIR)/lib/include $(CROSS_DIR)/lib/pkgconfig
	cd $(CROSS_DIR) && zip -r $(PWD)/$@ *
	gpg --sign --detach $(GNUTLS_DIR)-w32.zip

gnutls-$(GNUTLS_VERSION)-1gn.DevPak: $(GNUTLS_DIR)-w32.zip devcpp.tar
	rm -rf $(DEVCPP_DIR)
	mkdir -p $(DEVCPP_DIR)
	cd $(DEVCPP_DIR) && unzip ../$(GNUTLS_DIR)-w32.zip 
	cd $(DEVCPP_DIR) && tar xf ../devcpp.tar && sed -i 's/@VERSION@/$(GNUTLS_VERSION)/g' gnutls.DevPackage
	cd $(DEVCPP_DIR) && tar -cjf ../$@ .

devpak: gnutls-$(GNUTLS_VERSION)-1gn.DevPak

gnutls-w32: $(GNUTLS_DIR)-w32.zip

nettle: $(NETTLE_DIR)/.installed

gmp: $(GMP_DIR)/.installed

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

CONFIG_ENV := PKG_CONFIG_PATH="$(PKG_CONFIG_DIR)"
CONFIG_ENV += PKG_CONFIG_LIBDIR="$(PKG_CONFIG_DIR)"
CONFIG_FLAGS := --prefix=$(CROSS_DIR) --host=i686-w64-mingw32 --enable-shared --disable-static \
	--bindir=$(BIN_DIR) --libdir=$(LIB_DIR) --includedir=$(HEADERS_DIR) --enable-threads=win32 

$(P11_KIT_DIR)/.configured:
	test -f $(P11_KIT_FILE) || wget http://p11-glue.freedesktop.org/releases/$(P11_KIT_FILE)
	test -f $(P11_KIT_FILE).sig || wget http://p11-glue.freedesktop.org/releases/$(P11_KIT_FILE).sig
	gpg --verify $(P11_KIT_FILE).sig
	test -d $(P11_KIT_DIR) || tar -xf $(P11_KIT_FILE)
	cd $(P11_KIT_DIR) && LDFLAGS="$(LDFLAGS)" $(CONFIG_ENV) ./configure $(CONFIG_FLAGS) --without-libffi --without-libtasn1 && cd ..
	touch $@

$(P11_KIT_DIR)/.installed: $(P11_KIT_DIR)/.configured
	make -C $(P11_KIT_DIR) $(SMP)
	make -C $(P11_KIT_DIR) install -i
	-rm -rf $(HEADERS_DIR)/p11-kit
	-mv $(HEADERS_DIR)/p11-kit-1/p11-kit $(HEADERS_DIR)
	-rm -rf $(HEADERS_DIR)/p11-kit-1
	rm -f $(BIN_DIR)/p11-kit.exe
	touch $@

$(GMP_DIR)/.configured: 
	test -f $(GMP_FILE) || wget ftp://ftp.gmplib.org/pub/$(GMP_DIR)/$(GMP_FILE)
	test -f $(GMP_FILE).sig || wget ftp://ftp.gmplib.org/pub/$(GMP_DIR)/$(GMP_FILE).sig
	gpg --verify $(GMP_FILE).sig
	test -d $(GMP_DIR) || tar -xf $(GMP_FILE)
	cd $(GMP_DIR) && LDFLAGS="$(LDFLAGS)" $(CONFIG_ENV) ./configure $(CONFIG_FLAGS) --enable-fat --exec-prefix=$(LIB_DIR)  --oldincludedir=$(HEADERS_DIR) && cd ..
	cp $(GMP_DIR)/COPYING.LESSERv3 $(CROSS_DIR)/COPYING.GMP
	touch $@

$(GMP_DIR)/.installed: $(GMP_DIR)/.configured
	make -C $(GMP_DIR) $(SMP)
	make -C $(GMP_DIR) install -i
	-mkdir -p $(HEADERS_DIR)
	mv $(LIB_DIR)/include/* $(HEADERS_DIR)/
	rmdir $(LIB_DIR)/include/
	touch $@

$(NETTLE_DIR)/.configured: $(GMP_DIR)/.installed
	test -f $(NETTLE_FILE) || wget http://www.lysator.liu.se/~nisse/archive/$(NETTLE_FILE)
	test -f $(NETTLE_FILE).sig || wget http://www.lysator.liu.se/~nisse/archive/$(NETTLE_FILE).sig
	gpg --verify $(NETTLE_FILE).sig
	test -d $(NETTLE_DIR) || tar -xf $(NETTLE_FILE)
	cd $(NETTLE_DIR) && CFLAGS="-I$(HEADERS_DIR)" CXXFLAGS="-I$(HEADERS_DIR)" LDFLAGS="$(LDFLAGS)" $(CONFIG_ENV) ./configure $(CONFIG_FLAGS) --with-lib-path=$(LIB_DIR) && cd ..
	touch $@

#nettle messes up installation
$(NETTLE_DIR)/.installed: $(NETTLE_DIR)/.configured
	make -C $(NETTLE_DIR) $(SMP) -i
	make -C $(NETTLE_DIR) install -i
	rm -f $(LIB_DIR)/libnettle.a $(LIB_DIR)/libhogweed.a $(BIN_DIR)/nettle-hash.exe $(BIN_DIR)/nettle-lfib-stream.exe $(BIN_DIR)/pkcs1-conv.exe $(BIN_DIR)/sexp-conv.exe
	cp $(NETTLE_DIR)/libnettle.dll.a $(NETTLE_DIR)/libhogweed.dll.a $(LIB_DIR)/
	cp $(NETTLE_DIR)/libnettle*.dll $(NETTLE_DIR)/libhogweed*.dll $(BIN_DIR)/
	touch $@

GCC_DLLS=/usr/lib/gcc/i686-w64-mingw32/4.8/libgcc_s_sjlj-1.dll/libgcc_s_sjlj-1.dll /usr/i686-w64-mingw32/lib/libwinpthread-1.dll

$(GNUTLS_DIR)/.installed: $(GNUTLS_DIR)/.configured
	make -C $(GNUTLS_DIR) $(SMP)
	-cp $(GCC_DLLS) $(GNUTLS_DIR)/tests
	-cp $(GCC_DLLS) $(GNUTLS_DIR)/tests/safe-renegotiation
	-cp $(GCC_DLLS) $(GNUTLS_DIR)/tests/slow
	sed -i 's/^"$$@" >$$log_file/echo $$@|grep exe >\/dev\/null; if [ $$? == 0 ];then wine "$$@" >$$log_file;else \/bin\/true >$$log_file;fi/g' $(GNUTLS_DIR)/build-aux/test-driver
	make -C $(GNUTLS_DIR)/tests check $(SMP)
	make -C $(GNUTLS_DIR) install -i
	cp $(GNUTLS_DIR)/COPYING $(GNUTLS_DIR)/COPYING.LESSER $(CROSS_DIR)
	-cp $(GCC_DLLS) $(BIN_DIR)/
	touch $@

$(GNUTLS_DIR)/.configured: $(NETTLE_DIR)/.installed $(P11_KIT_DIR)/.installed
	test -f $(GNUTLS_FILE) || wget ftp://ftp.gnutls.org/gcrypt/gnutls/v3.2/$(GNUTLS_FILE)
	test -f $(GNUTLS_FILE).sig || wget ftp://ftp.gnutls.org/gcrypt/gnutls/v3.2/$(GNUTLS_FILE).sig
	gpg --verify $(GNUTLS_FILE).sig
	test -d $(GNUTLS_DIR) || tar -xf $(GNUTLS_FILE)
	cd $(GNUTLS_DIR) && \
		$(CONFIG_ENV) LDFLAGS="$(LDFLAGS) -L$(LIB_DIR)" CFLAGS="-I$(HEADERS_DIR)" CXXFLAGS="-I$(HEADERS_DIR)" \
		./configure $(CONFIG_FLAGS) --enable-local-libopts --disable-cxx \
		--enable-gcc-warnings --disable-libdane --disable-openssl-compatibility --with-included-libtasn1 && cd ..
	touch $@


clean:
	rm -rf $(CROSS_DIR) $(GNUTLS_DIR)/.installed $(NETTLE_DIR)/.installed $(GMP_DIR)/.installed $(P11_KIT_DIR)/.installed

dirclean:
	rm -rf $(CROSS_DIR) $(GNUTLS_DIR) $(NETTLE_DIR) $(GMP_DIR) $(P11_KIT_DIR)

