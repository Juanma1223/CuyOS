#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static bool print(const char *data, size_t length)
{
	const unsigned char *bytes = (const unsigned char *)data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
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
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char *format_begun_at = format++;

		if (*format == 'c')
		{
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
		}
		else if (*format == 's')
		{
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
		}
		else if (*format == 'i')
		{
			format++;
			int num = (int)va_arg(parameters, int);

			// This buffer is used to hold the smallest negative number as a string
			char buffer[12];
			// This points to the end of the array
			char *p = buffer + sizeof(buffer) - 1;
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
				size_t len = buffer + sizeof(buffer) - 1 - p;

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
		}
		else if (*format == 'p')
		{
			format++;
			void *ptr = va_arg(parameters, void *);
			// This buffer will store the whole formated hex value of the pointer we are printing
			char buffer[2 + sizeof(uintptr_t) * 2 + 1]; // "0x" + hex digits + null terminator
			buffer[0] = '0';
			buffer[1] = 'x';
			// Place the pointer at the end of the hex number
			char *p = &buffer[2 + sizeof(uintptr_t) * 2];
			// Add the null character
			*p = '\0';
			uintptr_t value = (uintptr_t)ptr;
			// Convert decimal into hex
			while (value)
			{
				*--p = "0123456789abcdef"[value % 16];
				value /= 16;
			}
			if (p == &buffer[2 + sizeof(uintptr_t) * 2])
			{
				*--p = '0';
			}
			size_t len = &buffer[2 + sizeof(uintptr_t) * 2] - p;
			if (maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(p, len))
				return -1;
			written += len;
		}
		else
		{
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}
