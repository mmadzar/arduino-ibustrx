#include "IbusMessage.h"

IbusMessage::IbusMessage(uint8_t *buffer)
{
  uint8_t m_length = buffer[1] + 1;
  // create a new buffer to hold the message
  m_buffer = new uint8_t[m_length];
  // copy part of message buffer into the new buffer
  for (uint8_t i = 0; i < m_length; i++)
  {
    m_buffer[i] = buffer[i];
  }
}
// clean up
IbusMessage::~IbusMessage()
{
  delete[] m_buffer;
  m_buffer = NULL;
}
// returns the source byte of the message
uint8_t IbusMessage::source()
{
  return m_buffer[0];
}
// returns the payload length of the message
uint8_t IbusMessage::length()
{
  return m_buffer[1];
}
// returns the destination byte of the message
uint8_t IbusMessage::destination()
{
  return m_buffer[2];
}
// returns the n'th byte of the message payload
uint8_t IbusMessage::b(uint8_t i)
{
  if (i > m_buffer[1] - 2)
  {
    return 0x00; // return 0x00 if an out of bound value has been requested
  }
  else
  {
    return m_buffer[3 + i];
  }
}

// returns hex representation of message
String IbusMessage::hex()
{
  String hexChars = "";
  String result = "";
  for (int i = 0; i < sizeof(m_buffer); i++)
  {
    byte b = m_buffer[i];
    hexChars = String(m_buffer[i], HEX);
    hexChars += " ";
    result += hexChars;
  }
  return result;
}

// returns copy of the buffered message
uint8_t *IbusMessage::bytes()
{
  uint8_t newBuffer[length() + 2];
  for (int i = 0; i < sizeof(m_buffer); i++)
  {
    newBuffer[i] = m_buffer[i];
  }
  return newBuffer;
}