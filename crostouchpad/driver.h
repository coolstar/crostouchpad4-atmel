#if !defined(_ATMELTP_H_)
#define _ATMELTP_H_

#pragma warning(disable:4200)  // suppress nameless struct/union warning
#pragma warning(disable:4201)  // suppress nameless struct/union warning
#pragma warning(disable:4214)  // suppress bit field types other than int warning
#include <initguid.h>
#include <wdm.h>

#pragma warning(default:4200)
#pragma warning(default:4201)
#pragma warning(default:4214)
#include <wdf.h>

#pragma warning(disable:4201)  // suppress nameless struct/union warning
#pragma warning(disable:4214)  // suppress bit field types other than int warning
#include <hidport.h>

#include "hidcommon.h"
#include "spb.h"
#include "atmel_mxt.h"

//
// String definitions
//

#define DRIVERNAME                 "crostouchpad4.sys: "

#define ATMELTP_POOL_TAG            (ULONG) 'lmtA'
#define ATMELTP_HARDWARE_IDS        L"CoolStar\\ATML0000\0\0"
#define ATMELTP_HARDWARE_IDS_LENGTH sizeof(ATMELTP_HARDWARE_IDS)

#define NTDEVICE_NAME_STRING       L"\\Device\\ATML0000"
#define SYMBOLIC_NAME_STRING       L"\\DosDevices\\ATML0000"

#define MT_TOUCH_COLLECTION0                                                   \
    0xa1, 0x02,                         /*   COLLECTION (Logical)		   */  \
	0x15, 0x00,                         /*       LOGICAL_MINIMUM (0)       */  \
	0x25, 0x01,                         /*       LOGICAL_MAXIMUM (1)       */  \
	0x09, 0x47,                         /*       USAGE (Confidence)	       */  \
	0x09, 0x42,                         /*       USAGE (Tip switch)        */  \
	0x95, 0x02,                         /*       REPORT_COUNT (2)          */  \
	0x75, 0x01,                         /*       REPORT_SIZE (1)           */  \
	0x81, 0x02,                         /*       INPUT (Data,Var,Abs)      */  \
	0x95, 0x06,                         /*       REPORT_COUNT (6)          */  \
	0x81, 0x03,                         /*       INPUT (Cnst,Ary,Abs)      */  \
	0x95, 0x01,                         /*       REPORT_COUNT (1)		   */  \
	0x75, 0x04,                         /*       REPORT_SIZE (4)		   */  \
	0x25, 0x10,                         /*       LOGICAL_MAXIMUM (16)	   */  \
	0x09, 0x51,                         /*       USAGE (Contact Identifier)*/  \
	0x81, 0x02,                         /*       INPUT (Data,Var,Abs)	   */  \
	0x75, 0x01,                         /*       REPORT_SIZE (1)	       */  \
	0x95, 0x04,                         /*       REPORT_COUNT (4)          */  \
	0x81, 0x03,                         /*       INPUT (Cnst,Var,Abs)	   */  \
	0x05, 0x01,                         /*       USAGE_PAGE (Generic Desk..*/  \
	0x75, 0x10,                         /*       REPORT_SIZE (16)          */  \
	0x55, 0x0e,                         /*       UNIT_EXPONENT (-2)        */  \
	/*0x65, 0x13,                         /*       UNIT(Inch,EngLinear)      */  \
	0x65, 0x11,                         /*       UNIT(Cm,SiLinear)      */  \
	0x09, 0x30,                         /*       USAGE (X)                 */  \
	0x15, 0x00,                         /*       LOGICAL_MINIMUM (0)	   */  \
	0x35, 0x00,                         /*       PHYSICAL_MINIMUM (0)      */  \

#define MT_TOUCH_COLLECTION1                                                   \
	0x95, 0x01,                         /*       REPORT_COUNT (1)          */  \
	0x81, 0x02,                         /*       INPUT (Data,Var,Abs)      */  \

#define MT_TOUCH_COLLECTION2													\
	0x09, 0x31,                         /*       USAGE (Y)                 */  \
	0x81, 0x02,                         /*       INPUT (Data,Var,Abs)      */  \
	0x05, 0x0d,                         /*       USAGE PAGE (Digitizers)   */ \
	0x09, 0x30,                         /*       USAGE (Tip Pressure)      */  \
	0x81, 0x02,                         /*       INPUT (Data,Var,Abs)      */ \
	0xc0,                               /*    END_COLLECTION */

#define MT_REF_TOUCH_COLLECTION												\
	MT_TOUCH_COLLECTION0 \
	0x26, 0x66, 0x03,                   /*       LOGICAL_MAXIMUM (870)     */  \
	0x46, 0x8E, 0x03,					/*       PHYSICAL_MAXIMUM (910)    */  \
	MT_TOUCH_COLLECTION1 \
	0x26, 0xE0, 0x01,                   /*       LOGICAL_MAXIMUM (480)     */  \
	0x46, 0xFE, 0x01,					/*       PHYSICAL_MAXIMUM (550)    */  \
	MT_TOUCH_COLLECTION2

#define USAGE_PAGES \
	0x55, 0x0C,                         /*    UNIT_EXPONENT (-4)         */  \
	0x66, 0x01, 0x10,                   /*    UNIT (Seconds)             */  \
	0x47, 0xff, 0xff, 0x00, 0x00,      /*     PHYSICAL_MAXIMUM (65535)   */  \
	0x27, 0xff, 0xff, 0x00, 0x00,         /*  LOGICAL_MAXIMUM (65535)      */  \
	0x75, 0x10,                           /*  REPORT_SIZE (16)                  */  \
	0x95, 0x01,                           /*  REPORT_COUNT (1)      */  \
	0x05, 0x0d,                         /*    USAGE_PAGE (Digitizers)     */  \
	0x09, 0x56,                         /*    USAGE (Scan Time)         */  \
	0x81, 0x02,                           /*  INPUT (Data,Var,Abs)              */  \
	0x09, 0x54,                         /*    USAGE (Contact count)     */  \
	0x25, 0x7f,                           /*  LOGICAL_MAXIMUM (127)      */  \
	0x95, 0x01,                         /*    REPORT_COUNT (1)     */  \
	0x75, 0x08,                         /*    REPORT_SIZE (8)         */  \
	0x81, 0x02,                         /*    INPUT (Data,Var,Abs)     */  \
	0x05, 0x09,                         /*    USAGE_PAGE (Button)              */  \
	0x09, 0x01,                         /*    USAGE_(Button 1)          */  \
	0x25, 0x01,                         /*    LOGICAL_MAXIMUM (1)               */  \
	0x75, 0x01,                         /*    REPORT_SIZE (1)                   */  \
	0x95, 0x01,                         /*    REPORT_COUNT (1)                  */  \
	0x81, 0x02,                         /*    INPUT (Data,Var,Abs)     */  \
	0x95, 0x07,                          /*   REPORT_COUNT (7)                   */  \
	0x81, 0x03,                         /*    INPUT (Cnst,Var,Abs)     */  \
	0x05, 0x0d,                         /*    USAGE_PAGE (Digitizer)     */  \
	0x85, REPORTID_MTOUCH,            /*   REPORT_ID (Feature)                   */  \
	0x09, 0x55,                         /*    USAGE (Contact Count Maximum)     */  \
	0x09, 0x59,                         /*    USAGE (Pad TYpe)     */  \
	0x75, 0x08,                         /*    REPORT_SIZE (8)      */  \
	0x95, 0x02,                         /*    REPORT_COUNT (2)     */  \
	0x25, 0x0f,                         /*    LOGICAL_MAXIMUM (15)     */  \
	0xb1, 0x02,                         /*    FEATURE (Data,Var,Abs)     */  \
	0xc0,                               /*   END_COLLECTION                      */  \
	\
	/*MOUSE TLC     */  \
	0x05, 0x01,                         /* USAGE_PAGE (Generic Desktop)          */  \
	0x09, 0x02,                         /* USAGE (Mouse)                         */  \
	0xa1, 0x01,                         /* COLLECTION (Application)             */  \
	0x85, REPORTID_MOUSE,               /*   REPORT_ID (Mouse)                   */  \
	0x09, 0x01,                         /*   USAGE (Pointer)                     */  \
	0xa1, 0x00,                         /*   COLLECTION (Physical)               */  \
	0x05, 0x09,                         /*     USAGE_PAGE (Button)               */  \
	0x19, 0x01,                         /*     USAGE_MINIMUM (Button 1)          */  \
	0x29, 0x02,                         /*     USAGE_MAXIMUM (Button 2)          */  \
	0x25, 0x01,                         /*     LOGICAL_MAXIMUM (1)               */  \
	0x75, 0x01,                         /*     REPORT_SIZE (1)                   */  \
	0x95, 0x02,                         /*     REPORT_COUNT (2)                  */  \
	0x81, 0x02,                         /*     INPUT (Data,Var,Abs)              */  \
	0x95, 0x06,                         /*     REPORT_COUNT (6)                  */  \
	0x81, 0x03,                         /*     INPUT (Cnst,Var,Abs)              */  \
	0x05, 0x01,                         /*     USAGE_PAGE (Generic Desktop)      */  \
	0x09, 0x30,                         /*     USAGE (X)                         */  \
	0x09, 0x31,                         /*     USAGE (Y)                         */  \
	0x75, 0x10,                         /*     REPORT_SIZE (16)                  */  \
	0x95, 0x02,                         /*     REPORT_COUNT (2)                  */  \
	0x25, 0x0a,                          /*    LOGICAL_MAXIMUM (10)           */  \
	0x81, 0x06,                         /*     INPUT (Data,Var,Rel)              */  \
	0xc0,                               /*   END_COLLECTION                      */  \
	0xc0,                                /*END_COLLECTION     */
//
// This is the default report descriptor for the Hid device provided
// by the mini driver in response to IOCTL_HID_GET_REPORT_DESCRIPTOR.
// 

typedef UCHAR HID_REPORT_DESCRIPTOR, *PHID_REPORT_DESCRIPTOR;

#ifdef DESCRIPTOR_DEF
HID_REPORT_DESCRIPTOR DefaultReportDescriptor[] = {
	//
	// Multitouch report starts here
	//
	//TOUCH PAD input TLC
	0x05, 0x0d,                         // USAGE_PAGE (Digitizers)          
	0x09, 0x05,                         // USAGE (Touch Pad)             
	0xa1, 0x01,                         // COLLECTION (Application)         
	0x85, REPORTID_MTOUCH,            //   REPORT_ID (Touch pad)              
	0x09, 0x22,                         //   USAGE (Finger)                 
	MT_REF_TOUCH_COLLECTION
	MT_REF_TOUCH_COLLECTION
	MT_REF_TOUCH_COLLECTION
	MT_REF_TOUCH_COLLECTION
	MT_REF_TOUCH_COLLECTION
	USAGE_PAGES
};


//
// This is the default HID descriptor returned by the mini driver
// in response to IOCTL_HID_GET_DEVICE_DESCRIPTOR. The size
// of report descriptor is currently the size of DefaultReportDescriptor.
//

CONST HID_DESCRIPTOR DefaultHidDescriptor = {
	0x09,   // length of HID descriptor
	0x21,   // descriptor type == HID  0x21
	0x0100, // hid spec release
	0x00,   // country code == Not Specified
	0x01,   // number of HID class descriptors
	{ 0x22,   // descriptor type 
	sizeof(DefaultReportDescriptor) }  // total length of report descriptor
};
#endif

#define true 1
#define false 0

typedef struct _ATMELTP_CONTEXT
{

	//
	// Handle back to the WDFDEVICE
	//

	WDFDEVICE FxDevice;

	WDFQUEUE ReportQueue;

	BYTE DeviceMode;

	SPB_CONTEXT I2CContext;

	WDFINTERRUPT Interrupt;

	BOOLEAN ConnectInterrupt;

	BOOLEAN RegsSet;

	BOOLEAN TrackpadBooted;

	WDFTIMER Timer;

	mxt_message_t lastmsg;

	struct mxt_rollup core;

	struct mxt_object	*msgprocobj;
	struct mxt_object	*cmdprocobj;

	struct mxt_id_info info;

	UINT32 TouchCount;

	uint8_t      Flags[20];

	USHORT XValue[20];

	USHORT YValue[20];

	USHORT    AREA[20];

	BOOLEAN BUTTONPRESSED;

	USHORT TIMEINT;

	LARGE_INTEGER LastTime;

	uint16_t max_x;
	uint16_t max_y;

	uint8_t max_x_hid[2];
	uint8_t max_y_hid[2];

	uint16_t phy_x;
	uint16_t phy_y;

	uint8_t phy_x_hid[2];
	uint8_t phy_y_hid[2];

	uint8_t num_touchids;
	uint8_t multitouch;

	struct t7_config t7_cfg;

	uint8_t t100_aux_ampl;
	uint8_t t100_aux_area;
	uint8_t t100_aux_vect;

	/* Cached parameters from object table */
	uint16_t T5_address;
	uint8_t T5_msg_size;
	uint8_t T6_reportid;
	uint16_t T6_address;
	uint16_t T7_address;
	uint8_t T9_reportid_min;
	uint8_t T9_reportid_max;
	uint8_t T19_reportid;

	bool T19_buttonstate;

	uint16_t T44_address;
	uint8_t T100_reportid_min;
	uint8_t T100_reportid_max;

	uint8_t max_reportid;

	uint8_t last_message_count;

} ATMELTP_CONTEXT, *PATMELTP_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(ATMELTP_CONTEXT, GetDeviceContext)

//
// Function definitions
//

DRIVER_INITIALIZE DriverEntry;

EVT_WDF_DRIVER_UNLOAD AtmelTPDriverUnload;

EVT_WDF_DRIVER_DEVICE_ADD AtmelTPEvtDeviceAdd;

EVT_WDFDEVICE_WDM_IRP_PREPROCESS AtmelTPEvtWdmPreprocessMnQueryId;

EVT_WDF_IO_QUEUE_IO_INTERNAL_DEVICE_CONTROL AtmelTPEvtInternalDeviceControl;

NTSTATUS
AtmelTPGetHidDescriptor(
IN WDFDEVICE Device,
IN WDFREQUEST Request
);

NTSTATUS
AtmelTPGetReportDescriptor(
IN WDFDEVICE Device,
IN WDFREQUEST Request,
OUT BOOLEAN* CompleteRequest
);

NTSTATUS
AtmelTPGetDeviceAttributes(
IN WDFREQUEST Request
);

NTSTATUS
AtmelTPGetString(
IN WDFREQUEST Request
);

NTSTATUS
AtmelTPWriteReport(
IN PATMELTP_CONTEXT DevContext,
IN WDFREQUEST Request
);

NTSTATUS
AtmelTPProcessVendorReport(
IN PATMELTP_CONTEXT DevContext,
IN PVOID ReportBuffer,
IN ULONG ReportBufferLen,
OUT size_t* BytesWritten
);

NTSTATUS
AtmelTPReadReport(
IN PATMELTP_CONTEXT DevContext,
IN WDFREQUEST Request,
OUT BOOLEAN* CompleteRequest
);

NTSTATUS
AtmelTPSetFeature(
IN PATMELTP_CONTEXT DevContext,
IN WDFREQUEST Request,
OUT BOOLEAN* CompleteRequest
);

NTSTATUS
AtmelTPGetFeature(
IN PATMELTP_CONTEXT DevContext,
IN WDFREQUEST Request,
OUT BOOLEAN* CompleteRequest
);

PCHAR
DbgHidInternalIoctlString(
IN ULONG        IoControlCode
);

//
// Helper macros
//

#define DEBUG_LEVEL_ERROR   1
#define DEBUG_LEVEL_INFO    2
#define DEBUG_LEVEL_VERBOSE 3

#define DBG_INIT  1
#define DBG_PNP   2
#define DBG_IOCTL 4

#if 0
#define AtmelTPPrint(dbglevel, dbgcatagory, fmt, ...) {          \
    if (AtmelTPDebugLevel >= dbglevel &&                         \
        (AtmelTPDebugCatagories && dbgcatagory))                 \
		    {                                                           \
        DbgPrint(DRIVERNAME);                                   \
        DbgPrint(fmt, __VA_ARGS__);                             \
		    }                                                           \
}
#else
#define AtmelTPPrint(dbglevel, fmt, ...) {                       \
}
#endif

#endif
