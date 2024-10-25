#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// We need the length pre-calculated because the data may not be null-terminated,
// and we are simply printing out a sequence of bytes without knowing their specific data type.
static bool print(const char *data, size_t length)
{
	for (size_t i = 0; i < length; i++)
		// Bytes representation of a char, then casted to a char
		if (putchar(data[i]) == EOF)
			return false;
	return true;
}

int printf(const char *restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0')
	{
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%')
		{
			if (format[0] == '%')
				format++;
			size_t len = 1;
			while (format[len] && format[len] != '%')
				len++;
			if (maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			format += len;
			written += len;
			continue;
		}

		const char *format_begun_at = format++;

		switch (*format)
		{
		case 'c':
			format++;
			char c = (char)va_arg(parameters, int /* char promotes to int */);
			if (!maxrem)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
			break;
		case 's':
			format++;
			const char *str = va_arg(parameters, const char *);
			size_t len = strlen(str);
			if (maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
			break;
		case 'i':
			format++;
			int num = (int)va_arg(parameters, int);

			// This buffer is used to hold the smallest negative number as a string
			char intBuffer[12];
			// This points to the end of the array
			char *p = intBuffer + sizeof(intBuffer) - 1;
			// Add null pointer to the end of the buffer
			*p = '\0'; // Null-terminate the buffer

			// Handle the case of 0 explicitly
			if (num == 0)
			{
				// Assign char 0 as the only number to display
				*--p = '0';
			}
			else
			{
				// Handle negative numbers
				bool is_negative = num < 0;
				unsigned int abs_value = is_negative ? -num : num;
				// Convert the integer to a string iterating backwards through buffer
				while (abs_value > 0)
				{
					*--p = '0' + (abs_value % 10);
					abs_value /= 10;
				}

				// Add the negative sign if necessary
				if (is_negative)
				{
					*--p = '-';
				}

				// Calculate the length of the resulting string, being p the pointer to the left over
				size_t len = intBuffer + sizeof(intBuffer) - 1 - p;

				// Check if the length exceeds the remaining buffer size
				if (maxrem < len)
				{
					// TODO: Set errno to EOVERFLOW.
					return -1;
				}

				// Print the string
				if (!print(p, len))
				{
					return -1;
				}

				// Update the written count
				written += len;
			}
			break;
		case 'p':
			format++;
			void *ptr = va_arg(parameters, void *);
			// This buffer will store the whole formated hex value of the pointer we are printing
			char hexBuffer[2 + sizeof(uintptr_t) * 2 + 1]; // "0x" + hex digits + null terminator
			hexBuffer[0] = '0';
			hexBuffer[1] = 'x';
			// Place the pointer at the end of the hex number
			char *hexPointer = &hexBuffer[2 + sizeof(uintptr_t) * 2];
			// Add the null character
			*hexPointer = '\0';
			uintptr_t value = (uintptr_t)ptr;
			// Convert decimal into hex
			while (value)
			{
				*--hexPointer = "0123456789abcdef"[value % 16];
				value /= 16;
			}
			if (hexPointer == &hexBuffer[2 + sizeof(uintptr_t) * 2])
			{
				*--hexPointer = '0';
			}
			size_t hexLen = &hexBuffer[2 + sizeof(uintptr_t) * 2] - hexPointer;
			if (maxrem < hexLen)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(hexPointer, hexLen))
				return -1;
			written += hexLen;
			break;

		default:
			format = format_begun_at;
			size_t strLen = strlen(format);
			if (maxrem < strLen)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, strLen))
				return -1;
			written += strLen;
			format += strLen;
			break;
		}
	}

	va_end(parameters);
	return written;
}
