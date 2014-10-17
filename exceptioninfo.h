/*
 *  Computer Graphics
 *
 *  exceptioninfo.h
 *
 *  Peter Jenke, Peter.Jenke@hig.se
 *
 *  Version 2013-09-26
 */

#ifndef EXCEPTIONINFO_H
#define EXCEPTIONINFO_H

#include <string>

class ExceptionInfo
{
public:
	ExceptionInfo(std::string causeString, unsigned short errCode);
	std::string getCause (void);
	unsigned short getErrCode (void);
private:
	std::string cause;
	unsigned short errCode;
};

#endif // EXCEPTIONINFO_H
