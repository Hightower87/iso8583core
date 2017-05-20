#include "ISOPackager.h"
#include "ISOFieldPackagers.h"

ISOPackager::ISOPackager() {
	setFieldPackager(0, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(4, "MESSAGE TYPE INDICATOR")));
	//TODO: bitmap string/binary packager
	setFieldPackager(1, boost::shared_ptr<ISOFieldPackagerBase> (new ISOBitMapPackager(16,	"BITMAP")));
	setFieldPackager(2, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLL_cn(19, "PRIMARY ACCOUNT NUMBER")));
	setFieldPackager(3, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(6, "PROCESSING CODE")));
	setFieldPackager(4, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(12, "AMOUNT, TRANSACTION")));
	setFieldPackager(5, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(12, "AMOUNT, SETTLEMENT")));
	setFieldPackager(6, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(12, "AMOUNT, CARDHOLDER BILLING")));
	setFieldPackager(7, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(10, "TRANSMISSION DATE AND TIME")));
	setFieldPackager(8, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(8, "AMOUNT, CARDHOLDER BILLING FEE")));
	setFieldPackager(9, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(8, "CONVERSION RATE, SETTLEMENT")));
	setFieldPackager(10, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(8, "CONVERSION RATE, CARDHOLDER BILLING")));
	setFieldPackager(11, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(6, "SYSTEM TRACE AUDIT NUMBER")));
	setFieldPackager(12, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(6, "TIME, LOCAL TRANSACTION")));
	setFieldPackager(13, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(4, "DATE, LOCAL TRANSACTION")));
	setFieldPackager(14, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(4, "DATE, EXPIRATION")));
	setFieldPackager(15, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(4, "DATE, SETTLEMENT")));
	setFieldPackager(16, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(4, "DATE, CONVERSION")));
	setFieldPackager(17, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(4, "DATE, CAPTURE")));
	setFieldPackager(18, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(4, "MERCHANTS TYPE")));
	setFieldPackager(19, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(3, "ACQUIRING INSTITUTION COUNTRY CODE")));
	setFieldPackager(20, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(3, "PAN EXTENDED COUNTRY CODE")));
	setFieldPackager(21, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(3, "FORWARDING INSTITUTION COUNTRY CODE")));
	setFieldPackager(22, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(3, "POINT OF SERVICE ENTRY MODE")));
	setFieldPackager(23, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(3, "CARD SEQUENCE NUMBER")));
	setFieldPackager(24, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(3, "NETWORK INTERNATIONAL IDENTIFIEER")));
	setFieldPackager(25, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(2, "POINT OF SERVICE CONDITION CODE")));
	setFieldPackager(26, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(2, "POINT OF SERVICE PIN CAPTURE CODE")));
	setFieldPackager(27, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(1, "AUTHORIZATION IDENTIFICATION RESP LEN")));
	setFieldPackager(28, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(9, "AMOUNT, TRANSACTION FEE")));
	setFieldPackager(29, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(9, "AMOUNT, SETTLEMENT FEE")));
	setFieldPackager(30, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(9, "AMOUNT, TRANSACTION PROCESSING FEE")));
	setFieldPackager(31, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(9, "AMOUNT, SETTLEMENT PROCESSING FEE")));
	setFieldPackager(32, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLL_n(11, "ACQUIRING INSTITUTION IDENT CODE")));
	setFieldPackager(33, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLL_n(11, "FORWARDING INSTITUTION IDENT CODE")));
	setFieldPackager(34, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLL_an(11, "FORWARDING INSTITUTION IDENT CODE")));
	setFieldPackager(35, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLL_z(37, "TRACK 2 DATA")));
	setFieldPackager(36, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(104, "TRACK 3 DATA")));
	setFieldPackager(37, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_an(12, "RETRIEVAL REFERENCE NUMBER")));
	setFieldPackager(38, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_an(6, "AUTHORIZATION IDENTIFICATION RESPONSE")));
	setFieldPackager(39, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_an(2, "RESPONSE CODE")));
	setFieldPackager(40, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_an(3, "SERVICE RESTRICTION CODE")));
	setFieldPackager(41, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_an(8, "CARD ACCEPTOR TERMINAL IDENTIFICACION")));
	setFieldPackager(42, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_an(15, "CARD ACCEPTOR IDENTIFICATION CODE")));
	setFieldPackager(43, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_an(40, "CARD ACCEPTOR NAME/LOCATION")));
	setFieldPackager(44, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLL_an(25, "ADITIONAL RESPONSE DATA")));
	setFieldPackager(45, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLL_an(76, "TRACK 1 DATA")));
	setFieldPackager(46, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(999, "ADITIONAL DATA - ISO")));
	setFieldPackager(47, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(999, "ADITIONAL DATA - NATIONAL")));
	setFieldPackager(48, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(999, "ADITIONAL DATA - PRIVATE")));
	setFieldPackager(49, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_an(3, "CURRENCY CODE, TRANSACTION")));
	setFieldPackager(50, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_an(3, "CURRENCY CODE, SETTLEMENT")));
	setFieldPackager(51, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_an(3, "CURRENCY CODE, CARDHOLDER BILLING")));
	setFieldPackager(52, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_b(8, "PIN DATA")));
	setFieldPackager(53, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_n(16, "SECURITY RELATED CONTROL INFORMATION")));
	setFieldPackager(54, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(120, "ADDITIONAL AMOUNTS")));
	setFieldPackager(55, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(999, "RESERVED ISO")));
	setFieldPackager(56, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(999, "RESERVED ISO")));
	setFieldPackager(57, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(999, "RESERVED NATIONAL")));
	setFieldPackager(58, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(999, "RESERVED NATIONAL")));
	setFieldPackager(59, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(999, "RESERVED NATIONAL")));
	setFieldPackager(60, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(999, "RESERVED PRIVATE")));
	setFieldPackager(61, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(999, "RESERVED PRIVATE")));
	setFieldPackager(62, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(999, "RESERVED PRIVATE")));
	setFieldPackager(63, boost::shared_ptr<ISOFieldPackagerBase> (new BCDLLL_an(999, "RESERVED PRIVATE")));
	setFieldPackager(64, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_b(8, "MESSAGE AUTHENTICATION CODE FIELD")));
	setFieldPackager(65, boost::shared_ptr<ISOFieldPackagerBase> (new FIX_b(1, "BITMAP, EXTENDED")));

}

ISOPackager::~ISOPackager() {}

