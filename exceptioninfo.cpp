/*
 *  Computer Graphics
 *
 *  exceptioninfo.cpp
 *
 *  Peter Jenke, Peter.Jenke@hig.se
 *
 *  Version 2013-09-26
 */

#include "exceptioninfo.h"

ExceptionInfo::ExceptionInfo(std::string causeValue, unsigned short errCode)
{
	cause = causeValue;
	this->errCode = errCode;
}

std::string ExceptionInfo::getCause (void)
{
	return cause;
}

unsigned short ExceptionInfo::getErrCode (void)
{
	return errCode;
}
