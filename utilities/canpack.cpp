#include <unistd.h>
#include <cstring>
#include "panda.h"

class CanPrint : public Panda::CanListener {
public:
	CanPrint() {};
	void newDataNotification(Panda::CanFrame* frame) {
		printf("New CAN read: %d.%06d,", (unsigned int)frame->sysTime.tv_sec, (int)frame->sysTime.tv_usec);

		printf("%d,%u,", (int)frame->bus, frame->messageID);

		for (int i =0; i < frame->dataLength; i++) {
			printf("%02x", frame->data[i]);
		}
		printf(",%d\n", frame->dataLength);
		
	}
};


char nissan1[] = {0x00, 0xF0, 0xA0, 0x09, 0x00, 0x00, 0x00, 0x01, 0x2A, 0x08, 0x85, 0x30, 0x00, 0x00, 0x00, 0x00, 0x9C, 0x40, 0x00, 0x00, 0xB8, 0x07, 0x59, 0x30, 0x80, 0x55, 0x80, 0x00, 0x00, 0x00, 0x01, 0x10, 0x06, 0x2D, 0x3F, 0x00, 0x00, 0xFF, 0xFE, 0x00, 0x00, 0xB9, 0x07, 0x17, 0x38, 0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xF1, 0xB3, 0x2B, 0x01, 0xC0, 0xD1, 0xA9, 0x3C, 0x3C, 0xDB, 0xC0, 0x78, 0x09, 0x00, 0x00, 0x00, 0x01, 0x2F, 0x07, 0xC4, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0xB4, 0x92, 0x65, 0x7A, 0x8D, 0x13, 0x08, 0x6C, 0x5F, 0xC0, 0x40, 0x05, 0x00, 0x00, 0x00, 0x00, 0xA8, 0x07, 0xFD, 0xE0, 0x2A, 0x5E, 0xA0, 0x7F, 0xF8, 0x00, 0x00, 0x00, 0x64, 0xB5, 0xF5, 0x75, 0x59, 0x50, 0x7F, 0x35, 0x72, 0x02, 0xAF, 0xB0, 0xB0, 0x10, 0x00, 0x00, 0x00, 0x02, 0x16, 0x04, 0x12, 0x98, 0x20, 0x00, 0x00, 0x00, 0x64, 0xB3, 0xC1, 0x9D, 0x9B, 0x92, 0x47, 0x4D, 0x6D, 0x33};


char nissan2[] = {0x00, 0xE0, 0x60, 0x04, 0x00, 0x00, 0x00, 0x00, 0x74, 0x08, 0xDA, 0xB0, 0x00, 0x00, 0x00, 0x11, 0x3D, 0xC0, 0x00, 0x00, 0x75, 0x08, 0x83, 0xB4, 0xE1, 0xA2, 0x16, 0x05, 0x32, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xC6, 0xFB, 0x6F, 0xE3, 0x61, 0x25, 0xBD, 0x8D, 0x9F};

char nissan3[] = {0x00, 0xE0, 0x58, 0x04, 0x00, 0x00, 0x00, 0x01, 0x35, 0x08, 0x6A, 0xC0, 0x80, 0x61, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x01, 0xE0, 0x02, 0xAB, 0xC0, 0x00, 0x01, 0x9A, 0x08, 0xD5, 0xC0, 0x00, 0x00, 0x80, 0x61, 0x00, 0x00, 0x00, 0x01, 0xB2, 0x04, 0xD2, 0xC0, 0x00, 0x00, 0xF8, 0x6B, 0x59, 0x64, 0xE6, 0x6A, 0x08, 0x1A, 0xCE, 0xC5, 0x80, 0x40, 0x04, 0x00, 0x00, 0x4F, 0x70, 0x00, 0x00, 0x20, 0x01, 0xA9, 0xEE, 0x20};

char nissan4[] = {0x00, 0xD0, 0x40, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x62, 0x08, 0xAB, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xCA, 0x03, 0x9F, 0x90, 0x00, 0x00, 0x00, 0x00, 0x3A, 0x50, 0xEF, 0x7A, 0xA1, 0xB5, 0xEA, 0x01, 0xCB, 0xAB};


int main(int argc, char **argv) {
	std::cout << "Starting " << argv[0] << std::endl;

	Panda::Can testCan;
	CanPrint mCanPrint;
	testCan.addObserver(&mCanPrint);
	
	testCan.initialize();
	testCan.startParsing();
	
	printf("\n------------- nissan1 ------------------\n");
	testCan.notificationCanRead(nissan1, sizeof(nissan1));
	usleep(100000);
	
	printf("\n------------- nissan2 ------------------\n");
	testCan.notificationCanRead(nissan2, sizeof(nissan2));
	usleep(100000);
	
	printf("\n------------- nissan3 ------------------\n");
	testCan.notificationCanRead(nissan3, sizeof(nissan3));
	usleep(100000);
	
	printf("\n------------- nissan4 ------------------\n");
	testCan.notificationCanRead(nissan4, sizeof(nissan4));
	usleep(100000);
	
	printf("\n------------- nissan1 but malformed ------------------\n");
	nissan1[64*2] = 0; // should be 2
	testCan.notificationCanRead(nissan1, sizeof(nissan1));
	usleep(100000);
	
	unsigned char testPack[256];
	Panda::CanFrame frame;
	frame.messageID = 420;
	frame.bus = 2;
	frame.dataLength = 64;
	memset(frame.data, 0, 64);
	frame.data[0] = 69;
	
	
	std::cout << "\n\n------------- Building a custom message size 64 -------------" << std::endl;
	int length = Panda::canFrameToBuffer(frame, testPack, 2);
	
	for	(int i = 0; i < length; i++) {
		if ( i % 16 == 0) {
			printf("\n");
		}
		printf("0x%02X ", testPack[i]);
	}
	printf("\n");
	

	std::cout << "Done." << std::endl;
	
	std::cout << "\nSending it through the parser:" << std::endl;
	testCan.notificationCanRead((char*)testPack, length);
	usleep(100000);
	
	
	
	frame.messageID = 1000;
	frame.bus = 1;
	frame.dataLength = 8;
	memset(frame.data, 0, 64);
	frame.data[0] = 0;
	frame.data[1] = 1;
	frame.data[2] = 2;
	frame.data[3] = 3;
	frame.data[4] = 4;
	frame.data[5] = 5;
	frame.data[6] = 6;
	frame.data[7] = 7;
	
	
	std::cout << "\n\n------------- Building a custom message size 8 -------------" << std::endl;
	length = Panda::canFrameToBuffer(frame, testPack, 2);
	
	for	(int i = 0; i < length; i++) {
		if ( i % 16 == 0) {
			printf("\n");
		}
		printf("0x%02X ", testPack[i]);
	}
	printf("\n");
	

	
	std::cout << "\nSending it through the parser:" << std::endl;
	testCan.notificationCanRead((char*)testPack, length);
	usleep(100000);
	
	

	frame.dataLength = 9;	// Invalid
	std::cout << "\n\n------------- Building an INVALID message -------------:" << std::endl;
	length = Panda::canFrameToBuffer(frame, testPack, 2);
	
	for	(int i = 0; i < length; i++) {
		if ( i % 16 == 0) {
			printf("\n");
		}
		printf("0x%02X ", testPack[i]);
	}
	printf("\n");
	

	
	std::cout << "\nSending it through the parser:" << std::endl;
	testCan.notificationCanRead((char*)testPack, length);
	usleep(100000);
	
	
	
	frame.messageID = 0x18DB33F1; // 417018865
	frame.bus = 1;
	frame.dataLength = 8;
	frame.data[0] = 0x02;
	frame.data[1] = 0x09;
	frame.data[2] = 0x02;
	frame.data[3] = 0;
	frame.data[4] = 0;
	frame.data[5] = 0;
	frame.data[6] = 0;
	frame.data[7] = 0;
	
	
	std::cout << "\n\n------------- Building an Extended OBD PID message -------------" << std::endl;
	length = Panda::canFrameToBuffer(frame, testPack, 2);
	
	for	(int i = 0; i < length; i++) {
		if ( i % 16 == 0) {
			printf("\n");
		}
		printf("0x%02X ", testPack[i]);
	}
	printf("\n");
	

	
	std::cout << "\nSending it through the parser:" << std::endl;
	testCan.notificationCanRead((char*)testPack, length);
	usleep(100000);
	
	
	
	
	
	testCan.stopParsing();
	std::cout << "Done." << std::endl;
	
	return 0;
}
