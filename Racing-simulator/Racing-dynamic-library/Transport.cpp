#include "Transport.h"

Transport::Transport(std::string type, int speed, int dtbr, int duration, std::string name_transport) 
	: type(type), speed(speed), dtbr(dtbr), duration(duration), name_transport(name_transport) {}

std::string Transport::name() const
{
	return name_transport;
}

std::string Transport::r_type() const
{
	return type;
}

int Transport::r_speed() const
{
	return speed;
}

int Transport::r_dtbr() const
{
	return dtbr;
}

int Transport::r_duration() const
{
	return duration;
}