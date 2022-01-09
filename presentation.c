/*-
 * Copyright (c) 2022 Michael Roe
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <unistd.h>

static wchar_t *presentation[] =
  {
    L"ff",
    L"fi",
    L"fl",
    L"ffi",
    L"ffl",
    L"\u017ft",
    L"st",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    L"\u0574\u0576",
    L"\u0574\u0565",
    L"\u057e\u056b",
    L"\u0574\u056d",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    L"\u05d9\u05b4",
    L"\u05bf",
    L"\u05f2\u05b7",
    L"\u05e2",
    L"\u05d0",
    L"\u05d3",
    L"\u05d4",
    L"\u05db",
    L"\u05dc",
    L"\u05dd",
    L"\u05e8",
    L"\u05ea",
    L"+",
    L"\u05e9\u05c1"
};

int main(int argc, char **argv)
{
int c;
int i;
int opt;
int supress_lrm = 0;
int dump_table =  0;

  setlocale(LC_ALL, getenv("LANG"));

  while ((opt = getopt(argc, argv, "dl")) != -1)
  {
    switch (opt)
    {
      case 'd':
        dump_table = 1;
	break;
      case 'l':
	supress_lrm = 1;
	break;
      default:
	break;
    }
  }

  if (dump_table)
  {
  for (i=0;i<sizeof(presentation)/sizeof(wchar_t *);i++)
    {
      if (presentation[i])
        wprintf(L"%04x %lc %ls\n", i + 0xfb00, i + 0xfb00, presentation[i]);
    }
  return 0;
  }

  while ((c = fgetwc(stdin)) != WEOF)
  {
    if ((c == 0x200e) || (c == 0x200f))
    {
      if (!supress_lrm)
      {
        putwchar(c);
      }
    }
    else if ((c >= 0xfb00) && (c <= 0xfb26 /* 0xfb47 */))  
    {
      if (presentation[c - 0xfb00])
      {
        wprintf(L"%ls", presentation[c - 0xfb00]);
      }
      else
      {
        wprintf(L"%lc", c);
      }
    }
    else
    {
      putwchar(c);
    }
  }
  return 0;
}
