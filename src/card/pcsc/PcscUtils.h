/*!
 * \brief toString method for PCSC_RETURNCODE and platform dependent
 * typedefs for PCSC types.
 *
 * \copyright Copyright (c) 2014-2020 Governikus GmbH & Co. KG, Germany
 */

#pragma once

#include <QMetaEnum>
#include <QString>
#include <QtGlobal>

#include <winscard.h>

#ifndef Q_OS_WIN
#include <wintypes.h>
#endif

/*
 * Because the three PC/SC implementations on Windows,
 * MacOS and Linux have sligtly different types, we typedef
 * an abstraction layer for those data types.
 */
#ifdef Q_OS_WIN
using PCSC_RETURNCODE = LONG;
using PCSC_INT = DWORD;
using PCSC_CHAR = TCHAR;
using PCSC_CHAR_PTR = TCHAR*;
using PCSC_UCHAR_PTR = LPBYTE;
using PCSC_CUCHAR_PTR = LPCBYTE;
#elif defined Q_OS_MACOS
using PCSC_RETURNCODE = int64_t; // avoid -Wc++11-narrowing and -Wsign-conversion
using PCSC_INT = uint32_t;
using PCSC_CHAR = char;
using PCSC_CHAR_PTR = char*;
using PCSC_UCHAR_PTR = uchar*;
using PCSC_CUCHAR_PTR = const uchar*;
#elif defined Q_OS_UNIX
using PCSC_RETURNCODE = LONG;
using PCSC_INT = DWORD;
using PCSC_CHAR = char;
using PCSC_CHAR_PTR = char*;
using PCSC_UCHAR_PTR = uchar*;
using PCSC_CUCHAR_PTR = const uchar*;
#endif


namespace governikus
{

class PcscUtils
{
	Q_GADGET

	private:
		PcscUtils() = delete;
		~PcscUtils() = delete;

	public:
		/**
		 * Error codes from http://msdn.microsoft.com/en-us/library/aa924526.aspx
		 */
		enum PcscReturnCode : PCSC_RETURNCODE
		{
			Scard_S_Success = SCARD_S_SUCCESS, /**< No error was encountered. */
			Scard_F_Internal_Error = SCARD_F_INTERNAL_ERROR, /**< An internal consistency check failed. */
			Scard_E_Cancelled = SCARD_E_CANCELLED, /**< The action was cancelled by an SCardCancel request. */
			Scard_E_Invalid_Handle = SCARD_E_INVALID_HANDLE, /**< The supplied handle was invalid. */
			Scard_E_Invalid_Parameter = SCARD_E_INVALID_PARAMETER, /**< One or more of the supplied parameters could not be properly interpreted. */
			Scard_E_Invalid_Target = SCARD_E_INVALID_TARGET, /**< Registry startup information is missing or invalid. */
			Scard_E_No_Memory = SCARD_E_NO_MEMORY, /**< Not enough memory available to complete this command. */
			Scard_F_Waited_Too_Long = SCARD_F_WAITED_TOO_LONG, /**< An internal consistency timer has expired. */
			Scard_E_Insufficient_Buffer = SCARD_E_INSUFFICIENT_BUFFER, /**< The data buffer to receive returned data is too small for the returned data. */
			Scard_E_Unknown_Reader = SCARD_E_UNKNOWN_READER, /**< The specified reader name is not recognized. */
			Scard_E_Timeout = SCARD_E_TIMEOUT, /**< The user-specified timeout value has expired. */
			Scard_E_Sharing_Violation = SCARD_E_SHARING_VIOLATION, /**< The smart card cannot be accessed because of other connections outstanding. */
			Scard_E_No_Smartcard = SCARD_E_NO_SMARTCARD, /**< The operation requires a Smart Card, but no Smart Card is currently in the device. */
			Scard_E_Unknown_Card = SCARD_E_UNKNOWN_CARD, /**< The specified smart card name is not recognized. */
			Scard_E_Cant_Dispose = SCARD_E_CANT_DISPOSE, /**< The system could not dispose of the media in the requested manner. */
			Scard_E_Proto_Mismatch = SCARD_E_PROTO_MISMATCH, /**< The requested protocols are incompatible with the protocol currently in use with the smart card. */
			Scard_E_Not_Ready = SCARD_E_NOT_READY, /**< The reader or smart card is not ready to accept commands. */
			Scard_E_Invalid_Value = SCARD_E_INVALID_VALUE, /**< One or more of the supplied parameters values could not be properly interpreted. */
			Scard_E_System_Cancelled = SCARD_E_SYSTEM_CANCELLED, /**< The action was cancelled by the system, presumably to log off or shut down. */
			Scard_F_Comm_Error = SCARD_F_COMM_ERROR, /**< An internal communications error has been detected. */
			Scard_F_Unknown_Error = SCARD_F_UNKNOWN_ERROR, /**< An internal error has been detected, but the source is unknown. */
			Scard_E_Invalid_Atr = SCARD_E_INVALID_ATR, /**< An ATR obtained from the registry is not a valid ATR string. */
			Scard_E_Not_Transacted = SCARD_E_NOT_TRANSACTED, /**< An attempt was made to end a non-existent transaction. */
			Scard_E_Reader_Unavailable = SCARD_E_READER_UNAVAILABLE, /**< The specified reader is not currently available for use. */
			Scard_P_Shutdown = SCARD_P_SHUTDOWN, /**< The operation has been aborted to allow the server application to exit. */
			Scard_E_Pci_Too_Small = SCARD_E_PCI_TOO_SMALL, /**< The PCI Receive buffer was too small. */
			Scard_E_Reader_Unsupported = SCARD_E_READER_UNSUPPORTED, /**< The reader driver does not meet minimal requirements for support. */
			Scard_E_Duplicate_Reader = SCARD_E_DUPLICATE_READER, /**< The reader driver did not produce a unique reader name. */
			Scard_E_Card_Unsupported = SCARD_E_CARD_UNSUPPORTED, /**< The smart card does not meet minimal requirements for support. */
			Scard_E_No_Service = SCARD_E_NO_SERVICE, /**< The Smart card resource manager is not running. */
			Scard_E_Service_Stopped = SCARD_E_SERVICE_STOPPED, /**< The Smart card resource manager has shut down. */
			Scard_E_Unsupported_Feature = SCARD_E_UNSUPPORTED_FEATURE, /**< This smart card does not support the requested feature. */
			Scard_E_Unexpected = SCARD_E_UNEXPECTED, /**< An unexpected card error has occurred. */
			Scard_E_Icc_Installation = SCARD_E_ICC_INSTALLATION, /**< No primary provider can be found for the smart card. */
			Scard_E_Icc_Createorder = SCARD_E_ICC_CREATEORDER, /**< The requested order of object creation is not supported. */

			Scard_E_Dir_Not_Found = SCARD_E_DIR_NOT_FOUND, /**< The identified directory does not exist in the smart card. */
			Scard_E_File_Not_Found = SCARD_E_FILE_NOT_FOUND, /**< The identified file does not exist in the smart card. */
			Scard_E_No_Dir = SCARD_E_NO_DIR, /**< The supplied path does not represent a smart card directory. */
			Scard_E_No_File = SCARD_E_NO_FILE, /**< The supplied path does not represent a smart card file. */
			Scard_E_No_Access = SCARD_E_NO_ACCESS, /**< Access is denied to this file. */
			Scard_E_Write_Too_Many = SCARD_E_WRITE_TOO_MANY, /**< The smart card does not have enough memory to store the information. */
			Scard_E_Bad_Seek = SCARD_E_BAD_SEEK, /**< There was an error trying to set the smart card file object pointer. */
			Scard_E_Invalid_Chv = SCARD_E_INVALID_CHV, /**< The supplied PIN is incorrect. */
			Scard_E_Unknown_Res_Mng = SCARD_E_UNKNOWN_RES_MNG, /**< An unrecognized error code was returned from a layered component. */
			Scard_E_No_Such_Certificate = SCARD_E_NO_SUCH_CERTIFICATE, /**< The requested certificate does not exist. */
			Scard_E_Certificate_Unavailable = SCARD_E_CERTIFICATE_UNAVAILABLE, /**< The requested certificate could not be obtained. */
			Scard_E_No_Readers_Available = SCARD_E_NO_READERS_AVAILABLE, /**< Cannot find a smart card reader. */
			Scard_E_Comm_Data_Lost = SCARD_E_COMM_DATA_LOST, /**< A communications error with the smart card has been detected. Retry the operation. */
			Scard_E_No_Key_Container = SCARD_E_NO_KEY_CONTAINER, /**< The requested key container does not exist on the smart card. */
			Scard_E_Server_Too_Busy = SCARD_E_SERVER_TOO_BUSY, /**< The Smart Card Resource Manager is too busy to complete this operation. */

			Scard_W_Unsupported_Card = SCARD_W_UNSUPPORTED_CARD, /**< The reader cannot communicate with the card, due to ATR string configuration conflicts. */
			Scard_W_Unresponsive_Card = SCARD_W_UNRESPONSIVE_CARD, /**< The smart card is not responding to a reset. */
			Scard_W_Unpowered_Card = SCARD_W_UNPOWERED_CARD, /**< Power has been removed from the smart card, so that further communication is not possible. */
			Scard_W_Reset_Card = SCARD_W_RESET_CARD, /**< The smart card has been reset, so any shared state information is invalid. */
			Scard_W_Removed_Card = SCARD_W_REMOVED_CARD, /**< The smart card has been removed, so further communication is not possible. */

			Scard_W_Security_Violation = SCARD_W_SECURITY_VIOLATION, /**< Access was denied because of a security violation. */
			Scard_W_Wrong_Chv = SCARD_W_WRONG_CHV, /**< The card cannot be accessed because the wrong PIN was presented. */
			Scard_W_Chv_Blocked = SCARD_W_CHV_BLOCKED, /**< The card cannot be accessed because the maximum number of PIN entry attempts has been reached. */
			Scard_W_Eof = SCARD_W_EOF, /**< The end of the smart card file has been reached. */
			Scard_W_Cancelled_By_User = SCARD_W_CANCELLED_BY_USER, /**< The user pressed "Cancel" on a Smart Card Selection Dialog. */
			Scard_W_Card_Not_Authenticated = SCARD_W_CARD_NOT_AUTHENTICATED /**< No PIN was presented to the smart card. */
		};
		Q_ENUM(PcscReturnCode)

		static QString toString(PCSC_RETURNCODE pCode);
};


/**
 * Make sure we do not use these macros directly in our code.
 */
#ifdef QT_NO_DEBUG
#undef SCARD_S_SUCCESS
#undef SCARD_F_INTERNAL_ERROR
#undef SCARD_E_CANCELLED
#undef SCARD_E_INVALID_HANDLE
#undef SCARD_E_INVALID_PARAMETER
#undef SCARD_E_INVALID_TARGET
#undef SCARD_E_NO_MEMORY
#undef SCARD_F_WAITED_TOO_LONG
#undef SCARD_E_INSUFFICIENT_BUFFER
#undef SCARD_E_UNKNOWN_READER
#undef SCARD_E_TIMEOUT
#undef SCARD_E_SHARING_VIOLATION
#undef SCARD_E_NO_SMARTCARD
#undef SCARD_E_UNKNOWN_CARD
#undef SCARD_E_CANT_DISPOSE
#undef SCARD_E_PROTO_MISMATCH
#undef SCARD_E_NOT_READY
#undef SCARD_E_INVALID_VALUE
#undef SCARD_E_SYSTEM_CANCELLED
#undef SCARD_F_COMM_ERROR
#undef SCARD_F_UNKNOWN_ERROR
#undef SCARD_E_INVALID_ATR
#undef SCARD_E_NOT_TRANSACTED
#undef SCARD_E_READER_UNAVAILABLE
#undef SCARD_P_SHUTDOWN
#undef SCARD_E_PCI_TOO_SMALL
#undef SCARD_E_READER_UNSUPPORTED
#undef SCARD_E_DUPLICATE_READER
#undef SCARD_E_CARD_UNSUPPORTED
#undef SCARD_E_NO_SERVICE
#undef SCARD_E_SERVICE_STOPPED
#undef SCARD_E_UNEXPECTED
#undef SCARD_E_UNSUPPORTED_FEATURE
#undef SCARD_E_ICC_INSTALLATION
#undef SCARD_E_ICC_CREATEORDER

#undef SCARD_E_DIR_NOT_FOUND
#undef SCARD_E_FILE_NOT_FOUND
#undef SCARD_E_NO_DIR
#undef SCARD_E_NO_FILE
#undef SCARD_E_NO_ACCESS
#undef SCARD_E_WRITE_TOO_MANY
#undef SCARD_E_BAD_SEEK
#undef SCARD_E_INVALID_CHV
#undef SCARD_E_UNKNOWN_RES_MNG
#undef SCARD_E_NO_SUCH_CERTIFICATE
#undef SCARD_E_CERTIFICATE_UNAVAILABLE
#undef SCARD_E_NO_READERS_AVAILABLE
#undef SCARD_E_COMM_DATA_LOST
#undef SCARD_E_NO_KEY_CONTAINER
#undef SCARD_E_SERVER_TOO_BUSY

#undef SCARD_W_UNSUPPORTED_CARD
#undef SCARD_W_UNRESPONSIVE_CARD
#undef SCARD_W_UNPOWERED_CARD
#undef SCARD_W_RESET_CARD
#undef SCARD_W_REMOVED_CARD

#undef SCARD_W_SECURITY_VIOLATION
#undef SCARD_W_WRONG_CHV
#undef SCARD_W_CHV_BLOCKED
#undef SCARD_W_EOF
#undef SCARD_W_CANCELLED_BY_USER
#undef SCARD_W_CARD_NOT_AUTHENTICATED
#endif

} // namespace governikus
