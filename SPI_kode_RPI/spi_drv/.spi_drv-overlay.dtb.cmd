cmd_/home/stud/SPI_kode_RPI/spi_drv/spi_drv-overlay.dtb := mkdir -p /home/stud/SPI_kode_RPI/spi_drv/ ; arm-poky-linux-gnueabi-gcc -E -Wp,-MD,/home/stud/SPI_kode_RPI/spi_drv/.spi_drv-overlay.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o /home/stud/SPI_kode_RPI/spi_drv/.spi_drv-overlay.dtb.dts.tmp /home/stud/SPI_kode_RPI/spi_drv/spi_drv-overlay.dts ; ./scripts/dtc/dtc -O dtb -o /home/stud/SPI_kode_RPI/spi_drv/spi_drv-overlay.dtb -b 0 -i/home/stud/SPI_kode_RPI/spi_drv/ -i./scripts/dtc/include-prefixes -Wno-unit_address_vs_reg -Wno-simple_bus_reg -Wno-unit_address_format -Wno-pci_bridge -Wno-pci_device_bus_num -Wno-pci_device_reg  -d /home/stud/SPI_kode_RPI/spi_drv/.spi_drv-overlay.dtb.d.dtc.tmp /home/stud/SPI_kode_RPI/spi_drv/.spi_drv-overlay.dtb.dts.tmp ; cat /home/stud/SPI_kode_RPI/spi_drv/.spi_drv-overlay.dtb.d.pre.tmp /home/stud/SPI_kode_RPI/spi_drv/.spi_drv-overlay.dtb.d.dtc.tmp > /home/stud/SPI_kode_RPI/spi_drv/.spi_drv-overlay.dtb.d

source_/home/stud/SPI_kode_RPI/spi_drv/spi_drv-overlay.dtb := /home/stud/SPI_kode_RPI/spi_drv/spi_drv-overlay.dts

deps_/home/stud/SPI_kode_RPI/spi_drv/spi_drv-overlay.dtb := \

/home/stud/SPI_kode_RPI/spi_drv/spi_drv-overlay.dtb: $(deps_/home/stud/SPI_kode_RPI/spi_drv/spi_drv-overlay.dtb)

$(deps_/home/stud/SPI_kode_RPI/spi_drv/spi_drv-overlay.dtb):
