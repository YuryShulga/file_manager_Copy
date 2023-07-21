#include "fm_exception.h"

fm_exception::fm_exception(std::string msg) :
	m_message{ msg }
{
}

std::string fm_exception::what()
{
	return m_message;
}
