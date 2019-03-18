struct usbTransfer
{
	struct libusb_transfer* xfr;
	unsigned char* buf;
};
