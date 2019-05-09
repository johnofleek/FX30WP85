DEPENDS += " \
        virtual/lk \
        yaffs2-utils-native \
        mtd-utils-native"

SRC_URI += "file://ubinize.cfg"
SRC_URI += "file://ubinize-user1.cfg"

INC_PR = "r0"

inherit ubi-image

# Install busybox mdev instead of udev. This is
# here just as a reminder, because we are doing
# manual installation of mdev.
# IMAGE_INSTALL += "busybox-mdev"

# Tools and helpers for i2c development
IMAGE_INSTALL += "i2cgpioctl"
IMAGE_INSTALL += "i2c-tools"

# Install kernel modules
IMAGE_INSTALL += "kernel-modules"

# Install device trees to rootfs (/boot directory is default location).
IMAGE_INSTALL += "kernel-devicetree"

# Add some extra packages for tool integration
IMAGE_INSTALL += "lttng-ust"
IMAGE_INSTALL += "lttng-modules"

# Add linkmon app to monitor USB link
IMAGE_INSTALL += "linkmon"

# Add WiFi TI drivers, tools, and scripts
# JT
# IMAGE_INSTALL += "ti-compat-wireless"
# IMAGE_INSTALL += "sierra-init-tiwifi"

# JT
#IMAGE_INSTALL += "python-ptest"
IMAGE_INSTALL += "libpython2"
#IMAGE_INSTALL += "python-dbg"
IMAGE_INSTALL += "python-2to3"
#IMAGE_INSTALL += "python-audio"
#IMAGE_INSTALL += "python-bsddb"
IMAGE_INSTALL += "python-codecs"
IMAGE_INSTALL += "python-compile"
IMAGE_INSTALL += "python-compiler"
IMAGE_INSTALL += "python-compression"
IMAGE_INSTALL += "python-core"
IMAGE_INSTALL += "python-crypt"
IMAGE_INSTALL += "python-ctypes"
IMAGE_INSTALL += "python-curses"
IMAGE_INSTALL += "python-datetime"
IMAGE_INSTALL += "python-db"
#IMAGE_INSTALL += "python-debugger"
#IMAGE_INSTALL += "python-dev"
#IMAGE_INSTALL += "python-difflib"
#IMAGE_INSTALL += "python-distutils-staticdev"
#IMAGE_INSTALL += "python-distutils"
#IMAGE_INSTALL += "python-doctest"
#IMAGE_INSTALL += "python-elementtree"
IMAGE_INSTALL += "python-email"
IMAGE_INSTALL += "python-fcntl"
#IMAGE_INSTALL += "python-gdbm"
#IMAGE_INSTALL += "python-hotshot"
#IMAGE_INSTALL += "python-html"
IMAGE_INSTALL += "python-idle"
#IMAGE_INSTALL += "python-image"
IMAGE_INSTALL += "python-importlib"
IMAGE_INSTALL += "python-io"
IMAGE_INSTALL += "python-json"
#IMAGE_INSTALL += "python-lang"
IMAGE_INSTALL += "python-logging"
#IMAGE_INSTALL += "python-mailbox"
IMAGE_INSTALL += "python-math"
IMAGE_INSTALL += "python-mime"
#IMAGE_INSTALL += "python-mmap"
IMAGE_INSTALL += "python-multiprocessing"
#IMAGE_INSTALL += "python-netclient"
#IMAGE_INSTALL += "python-netserver"
IMAGE_INSTALL += "python-numbers"
IMAGE_INSTALL += "python-pickle"
#IMAGE_INSTALL += "python-pkgutil"
#IMAGE_INSTALL += "python-pprint"
#IMAGE_INSTALL += "python-profile"
#IMAGE_INSTALL += "python-pydoc"
IMAGE_INSTALL += "python-re"
IMAGE_INSTALL += "python-readline"
IMAGE_INSTALL += "python-resource"
#IMAGE_INSTALL += "python-robotparser"
#IMAGE_INSTALL += "python-shell"
IMAGE_INSTALL += "python-smtpd"
IMAGE_INSTALL += "python-sqlite3"
#IMAGE_INSTALL += "python-sqlite3-tests"
#IMAGE_INSTALL += "python-stringold"
IMAGE_INSTALL += "python-subprocess"
IMAGE_INSTALL += "python-syslog"
#IMAGE_INSTALL += "python-terminal"
#IMAGE_INSTALL += "python-tests"
#IMAGE_INSTALL += "python-textutils"
IMAGE_INSTALL += "python-threading"
#IMAGE_INSTALL += "python-tkinter"
#IMAGE_INSTALL += "python-unittest"
#IMAGE_INSTALL += "python-unixadmin"
#IMAGE_INSTALL += "python-xml"
#IMAGE_INSTALL += "python-xmlrpc"
#IMAGE_INSTALL += "python-zlib"
IMAGE_INSTALL += "python-modules"
IMAGE_INSTALL += "python-misc"
#IMAGE_INSTALL += "python-man"
# JT END

# Create UBI images for ROOT and USER1 partitions. If it becomes longer, this
# function should be optimized (creation of sub-methods, etc.)
prepare_ubi_ps() {
    local page_size=$1

    # Initially, set for root partition
    local ubi_path="${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.${page_size}.ubi"
    local ubi_link_path="${DEPLOY_DIR_IMAGE}/${IMAGE_LINK_NAME}.${page_size}.ubi"
    local ubinize_cfg=${WORKDIR}/gen_ubinize.cfg

    # Process root partition UBI
    cp -af ${WORKDIR}/ubinize.cfg $ubinize_cfg
    sed -i -e "s|@@ROOTFS_PATH@@|${UBI_ROOTFS_PATH}|g" $ubinize_cfg
    sed -i -e "s|@@ROOTFS_SIZE@@|${UBI_ROOTFS_SIZE}|g" $ubinize_cfg
    create_ubi_image $page_size $ubinize_cfg $ubi_path $ubi_link_path

    # Process USER1 UBI
    ubi_path="${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}-user1.${page_size}.ubi"
    ubi_link_path="${DEPLOY_DIR_IMAGE}/${IMAGE_LINK_NAME}-user1.${page_size}.ubi"
    ubinize_cfg=${WORKDIR}/gen_ubinize.cfg

    cp -af ${WORKDIR}/ubinize-user1.cfg $ubinize_cfg
    sed -i -e "s|@@USER1_PATH@@|${UBI_USER1_PATH}|g" $ubinize_cfg
    sed -i -e "s|@@USER1_SIZE@@|${UBI_USER1_SIZE}|g" $ubinize_cfg
    create_ubi_image $page_size $ubinize_cfg $ubi_path $ubi_link_path
}

# Create UBI images
prepare_ubi() {
    prepare_ubi_ps '2k'
    prepare_ubi_ps '4k'

    # Default image (no bs suffix) to 4k
    ubi_link_path_def="${DEPLOY_DIR_IMAGE}/${IMAGE_LINK_NAME}.4k.ubi"
    ubi_link_path="${DEPLOY_DIR_IMAGE}/${IMAGE_LINK_NAME}.ubi"
    rm -f $ubi_link_path
    ln -s $(basename $ubi_link_path_def) $ubi_link_path
}

default_rootfs_ps() {
    # Default yaffs2 image to 4k
    ln -sf ${IMAGE_NAME}.rootfs.4k.yaffs2 ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.rootfs.yaffs2

    # Default rootfs to ubi for 2k
    ln -sf ${IMAGE_LINK_NAME}.2k.ubi    ${DEPLOY_DIR_IMAGE}/${IMAGE_LINK_NAME}.2k.default

    # Default rootfs to yaffs2 for 4k
    ln -sf ${IMAGE_LINK_NAME}.4k.yaffs2 ${DEPLOY_DIR_IMAGE}/${IMAGE_LINK_NAME}.4k.default
}

do_rootfs[postfuncs] += "prepare_ubi"
do_rootfs[postfuncs] += "default_rootfs_ps"

# Re-enable fetch & unpack tasks, because of bug(s) in Yocto 1.6 .
do_fetch2[dirs] = "${DL_DIR}"
python do_fetch2() {
    bb.build.exec_func('base_do_fetch', d)
}

addtask fetch2

do_unpack2[dirs] = "${WORKDIR}"
python do_unpack2() {
    bb.build.exec_func('base_do_unpack', d)
}

addtask unpack2 before do_rootfs

