/**
	@file
	Arduino library for communication to LoRa Module via UART 
*/
/*
	LoRaUART.cpp - Arduino library for communication to LoRa module via UART.

	Library:: LoRaUART
*/

/* _____PROJECT INCLUDES_____________________________________________________ */
#include "LoRaUART.h"

uint32_t LoRaUART::initLoRa()
{
	_CmdType = requestAPI;
	_ATcmd = ATcmdInitLoRa;
	_RWmode = readCmd;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n"; 
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	int first,second;
	unsigned long responseStatus;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';
		responseStatus=strtoul(q,NULL,16);
		switch(responseStatus)
		{
			case 0: return 1; break;
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}
}	

uint32_t LoRaUART::activateLoRa()
{
	_CmdType = requestAPI;
	_ATcmd = ATcmdActivateLoRa;
	_RWmode = readCmd;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())

	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	int first,second;
	unsigned long responseStatus;


	if(response.substring(0,4) == "$RES")
	{
		first = response.indexOf(',');
		second = response.indexOf(',',first+1);
		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';
		responseStatus=strtoul(q,NULL,16);
		switch(responseStatus)
		{
			case 0: return 1; break;
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}
}

uint32_t LoRaUART::deactivateLoRa()
{
	_CmdType = requestAPI;
 	_ATcmd = ATcmdDeactivateLoRa;
 	_RWmode = readCmd;
 	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
 	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	int first,second;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		responseStatus=strtoul(q,NULL,16);
		switch(responseStatus)
		{
			case 0: return 1; break;
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}
}

uint32_t LoRaUART::restoreDefault()
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdRestoreDefault;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	int first,second;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';
		responseStatus=strtoul(q,NULL,16);
		switch(responseStatus)
		{
			case 0: return 1; break;
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}
}

uint32_t LoRaUART::getBaudRate()
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdBaudRate;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	char b[3];
	int first,second,third;
	unsigned long responseStatus;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		b[0]= response.charAt(second+1);
		b[1]= response.charAt(second+1);
		b[2]= '\0';

		responseStatus=strtoul(q,NULL,16);
		_baudrate = strtoul(b,NULL,16);

		switch(responseStatus)
		{
			case 0: switch(_baudrate)
					{
						case 0 : return 4800; break;
						case 1 : return 9600; break;
						case 2 : return 19200; break;
						case 3 : return 57600; break;
						case 4 : return 115200; break;
					}
					break;	
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}

}

uint32_t LoRaUART::setBaudRate(uint32_t baudrate)
{
	_CmdType = requestAPI;
	_RWmode = writeCmd;
	_ATcmd = ATcmdBaudRate;

	switch(baudrate)
	{
		case 4800 : _baudrate = 0x00; break;
		case 9600 : _baudrate = 0x01; break;
		case 19200 : _baudrate = 0x02; break;
		case 57600 : _baudrate = 0x03; break;
		case 115200 : _baudrate = 0x04; break;
		default: _baudrate = 0x01;
	};
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + ',' + _baudrate + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	int first,second;
	unsigned long responseStatus;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		responseStatus=strtoul(q,NULL,16);
		switch(responseStatus)
		{
			case 0: return 1; break;
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}
}

uint32_t LoRaUART::getDeviceEUI(uint8_t* deviceEUI)
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdDeviceEUI;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	char temp[3];
	int first,second,third;
	unsigned long responseStatus;


	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		responseStatus=strtoul(q,NULL,16);

		for(int j = third, int a=0; response.charAt(j)!='\r\n'; j++)
		{
			if(response.charAt(j)==',')
			{
				temp[0]= response.charAt(j+1);
				temp[1]= response.charAt(j+2);
				temp[2]= '\0';
				*(deviceEUI+a) = strtoul(temp,NULL,16);
			}
		}

		switch(responseStatus)
		{
			case 0: return 1; break;
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}

}

uint32_t LoRaUART::setDeviceEUI(uint8_t* deviceEUI, int EUIlength)
{
	_CmdType = requestAPI;
	_RWmode = writeCmd;
	_ATcmd = ATcmdDeviceEUI;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + ",";
	for(int i=1; i<=EUIlength; i++)
	{
		if(i!=EUIlength)
			requestCmd = requestCmd + *deviceEUI + ',';
		else
			requestCmd = requestCmd + *deviceEUI;
		deviceEUI++;
	}
	requestCmd= requestCmd + "\r\n";

	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	int first,second;
	unsigned long responseStatus;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';
		responseStatus = strtoul(q,NULL,16);
		switch(responseStatus)
		{
			case 0: return 1; break;
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}
}

uint32_t LoRaUART::getApplicationEUI(uint8_t* applicationEUI)
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdApplicationEUI;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	char temp[3];
	int first,second,third;
	unsigned long responseStatus;


	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		responseStatus=strtoul(q,NULL,16);

		for(int j = third, int a=0; response.charAt(j)!='\r\n'; j++)
		{
			if(response.charAt(j)==',')
			{
				temp[0]= response.charAt(j+1);
				temp[1]= response.charAt(j+2);
				temp[2]= '\0';
				*(applicationEUI+a) = strtoul(temp,NULL,16);
			}
		}

		switch(responseStatus)
		{
			case 0: return 1; break;
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}
}

uint32_t LoRaUART::setApplicationEUI(uint8_t* applicationEUI, int EUIlength)
{
	_CmdType = requestAPI;
	_RWmode = writeCmd;
	_ATcmd = ATcmdApplicationEUI;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + ",";
	for(int i=1; i<=EUIlength; i++)
	{
		if(i!=EUIlength)
			requestCmd = requestCmd + *applicationEUI + ',';
		else
			requestCmd = requestCmd + *applicationEUI;
		applicationEUI++;
	}
	requestCmd = requestCmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}
}

uint32_t LoRaUART::getApplicationKey(uint8_t* _applicationKey)
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdApplicationKey;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	char temp[3];
	int first,second,third;
	unsigned long responseStatus;


	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		responseStatus=strtoul(q,NULL,16);

		for(int j = third, int a=0; response.charAt(j)!='\r\n'; j++)
		{
			if(response.charAt(j)==',')
			{
				temp[0]= response.charAt(j+1);
				temp[1]= response.charAt(j+2);
				temp[2]= '\0';
				*(_applicationKey+a) = strtoul(temp,NULL,16);
			}
		}

		switch(responseStatus)
		{
			case 0: return 1; break;
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}
}	

uint32_t LoRaUART::getNetworkKey(uint8_t* _networkKey)
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdNetworkKey;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	char temp[3];
	int first,second,third;
	unsigned long responseStatus;


	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		responseStatus=strtoul(q,NULL,16);

		for(int j = third, int a=0; response.charAt(j)!='\r\n'; j++)
		{
			if(response.charAt(j)==',')
			{
				temp[0]= response.charAt(j+1);
				temp[1]= response.charAt(j+2);
				temp[2]= '\0';
				*(_networkKey+a) = strtoul(temp,NULL,16);
			}
		}

		switch(responseStatus)
		{
			case 0: return 1; break;
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}
}	

uint32_t LoRaUART::getDeviceAddress(uint8_t* _deviceAddress)
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdDeviceAddr;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	char temp[3];
	int first,second,third;
	unsigned long responseStatus;


	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		responseStatus=strtoul(q,NULL,16);

		for(int j = third, int a=0; response.charAt(j)!='\r\n'; j++)
		{
			if(response.charAt(j)==',')
			{
				temp[0]= response.charAt(j+1);
				temp[1]= response.charAt(j+2);
				temp[2]= '\0';
				*(_deviceAddress+a) = strtoul(temp,NULL,16);
			}
		}

		switch(responseStatus)
		{
			case 0: return 1; break;
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}
}	

uint32_t LoRaUART::getNetworkConnType()
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdNetworkConnType;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	char b[3];
	int first,second,third;
	unsigned long responseStatus;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		b[0]= response.charAt(second+1);
		b[1]= response.charAt(second+1);
		b[2]= '\0';

		responseStatus=strtoul(q,NULL,16);
		_netConnType = strtoul(b,NULL,16);

		switch(responseStatus)
		{
			case 0: switch(_netConnType)						//success
					{
						case 0 : return 0; break;				//Activation By Personalisation
						case 1 : return 1; break;				//Over The Air Activation
					}
					break;	
			case 1: return -1; break;							//invalid parameter
			case 2: return -2; break;							//AT command error
		}	
	}
}

uint32_t LoRaUART::getNetworkID(uint8_t* _networkID)
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdNetworkID;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}	

	char q[3];
	char temp[3];
	int first,second,third;
	unsigned long responseStatus;


	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		responseStatus=strtoul(q,NULL,16);

		for(int j = third, int a=0; response.charAt(j)!='\r\n'; j++)
		{
			if(response.charAt(j)==',')
			{
				temp[0]= response.charAt(j+1);
				temp[1]= response.charAt(j+2);
				temp[2]= '\0';
				*(_networkID+a) = strtoul(temp,NULL,16);
			}
		}

		switch(responseStatus)
		{
			case 0: return 1; break;
			case 1: return -1; break;
			case 2: return -2; break;
		}	
	}
}

uint32_t LoRaUART::getADRStatus()
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdADRStatus;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	char b[3];
	int first,second,third;
	unsigned long responseStatus;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		b[0]= response.charAt(second+1);
		b[1]= response.charAt(second+1);
		b[2]= '\0';

		responseStatus=strtoul(q,NULL,16);
		_ADRStatus = strtoul(b,NULL,16);

		switch(responseStatus)
		{
			case 0: switch(_ADRStatus)							//success
					{
						case 0 : return 0; break;				//ADR On
						case 1 : return 1; break;				//ADR Off
					}
					break;	
			case 1: return -1; break;							//invalid parameter
			case 2: return -2; break;							//AT command error
		}	
	}	
}

uint32_t LoRaUART::getUplinkAckStatus()
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdUplinkAckStatus;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	char b[3];
	int first,second,third;
	unsigned long responseStatus;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		b[0]= response.charAt(second+1);
		b[1]= response.charAt(second+1);
		b[2]= '\0';

		responseStatus=strtoul(q,NULL,16);
		_uplinkAckStatus = strtoul(b,NULL,16);

		switch(responseStatus)
		{
			case 0: switch(_uplinkAckStatus)					//success
					{
						case 0 : return 0; break;				//Uplink Acknowledgement On
						case 1 : return 1; break;				//Uplink Acknowledgement Off
					}
					break;	
			case 1: return -1; break;							//invalid parameter
			case 2: return -2; break;							//AT command error
		}	
	}		
}

uint32_t LoRaUART::getDataConfirmationRetries()
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdDataConfirmRetries;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	char b[3];
	int first,second,third;
	unsigned long responseStatus;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		b[0]= response.charAt(second+1);
		b[1]= response.charAt(second+1);
		b[2]= '\0';

		responseStatus=strtoul(q,NULL,16);
		_dataConfirmRetries = strtoul(b,NULL,16);

		switch(responseStatus)
		{
			case 0: return _dataConfirmRetries;					//Data Confirmation Retries Value
					break;	
			case 1: return -1; break;							//invalid parameter
			case 2: return -2; break;							//AT command error
		}	
	}	
}

uint32_t LoRaUART::getDataRate()
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdDefaultDataRate;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}	

	char q[3];
	char b[3];
	int first,second,third;
	unsigned long responseStatus;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		b[0]= response.charAt(second+1);
		b[1]= response.charAt(second+1);
		b[2]= '\0';

		responseStatus=strtoul(q,NULL,16);
		_defaultDataRate = strtoul(b,NULL,16);

		switch(responseStatus)
		{
			case 0: return _defaultDataRate;					//Default data Rate
					break;	
			case 1: return -1; break;							//invalid parameter
			case 2: return -2; break;							//AT command error
		}	
	}
}

void LoRaUART::getPowerSavingStatus()
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdPowerSaveMode;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	char b[3];
	int first,second,third;
	unsigned long responseStatus;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		b[0]= response.charAt(second+1);
		b[1]= response.charAt(second+1);
		b[2]= '\0';

		responseStatus=strtoul(q,NULL,16);
		_powSaveStatus = strtoul(b,NULL,16);

		switch(responseStatus)
		{
			case 0: switch(_powSaveStatus)						//success
					{
						case 0 : return 0; break;				//Power Saving Mode On
						case 1 : return 1; break;				//Power Saving Mode Off
					}
					break;	
			case 1: return -1; break;							//invalid parameter
			case 2: return -2; break;							//AT command error
		}	
	}	
}

void LoRaUART::getClassSelection()
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdClassSelection;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}	

	char q[3];
	char b[3];
	int first,second,third;
	unsigned long responseStatus;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		third = response.indexOf(',',second+1);

		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		b[0]= response.charAt(second+1);
		b[1]= response.charAt(second+1);
		b[2]= '\0';

		responseStatus=strtoul(q,NULL,16);
		_classSelection = strtoul(b,NULL,16);

		switch(responseStatus)
		{
			case 0: switch(_classSelection)						//success
					{
						case 0 : return 0; break;				//Class C
						case 1 : return 1; break;				//Class A
					}
					break;	
			case 1: return -1; break;							//invalid parameter
			case 2: return -2; break;							//AT command error
		}	
	}
}

void LoRaUART::moduleTest()
{
	_CmdType = requestAPI;
	_RWmode = readCmd;
	_ATcmd = ATcmdModuleTestCmd;
	requestCmd= requestCmd + _CmdType + ',' + _RWmode + ',' + _ATcmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

	char q[3];
	int first,second;
	unsigned long responseStatus;

	if(response.substring(0,4) == "$RES")
	{
		first=response.indexOf(',');
		second = response.indexOf(',',first+1);
		q[0]=response.charAt(second+1);
		q[1]=response.charAt(second+2);
		q[2]='\0';

		responseStatus=strtoul(q,NULL,16);
		switch(responseStatus)
		{
			case 0: return 1; break;				//success
			case 1: return -1; break;				//invalid parameter
			case 2: return -2; break;				//AT command error
		}	
	}
}

void LoRaUART::sendUplink(uint8_t portnum, int datalength, uint8_t* data)
{
	_CmdType = uplinkAPI;
	_portnum = portnum;
	_datalength = datalength;
	requestCmd= requestCmd + _CmdType + ',' + _portnum + ',' + _datalength + ",";
	for(int i=1; i<=_datalength; i++)
	{
		if(i!=_datalength)
			requestCmd = requestCmd + *data + ',';
		else
			requestCmd = requestCmd + *data;
		data++;
	}
	requestCmd = requestCmd + "\r\n";
	for(int i=0; requestCmd.charAt(i)!="\0"; i++)
		Serial.write(requestCmd.charAt(i));

	int t= millis();
	while(!Serial.available())
	if(millis()-t >1000)
		_timeout=true;
	else
	{			
		while(Serial.available())
		{
			_incomingByte = (char)Serial.read();
			response += _incomingByte;
		}	
	}

}

