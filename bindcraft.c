/* 
______ _           _ _____            __ _   
| ___ (_)         | /  __ \          / _| |  
| |_/ /_ _ __   __| | /  \/_ __ __ _| |_| |_ 
| ___ \ | '_ \ / _` | |   | '__/ _` |  _| __|
| |_/ / | | | | (_| | \__/\ | | (_| | | | |_ 
\____/|_|_| |_|\__,_|\____/_|  \__,_|_|  \__|
 
Copyright (C) 2018  Anthony Green <green@redhat.com>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
                                            
*/

#include <netinet/in.h>
#include <dlfcn.h>

int (*_bind)(int, const struct sockaddr *, socklen_t);
int (*_connect)(int, const struct sockaddr *, socklen_t);

void _init (void)
{
  _bind = dlsym (RTLD_NEXT, "bind");
  _connect = dlsym (RTLD_NEXT, "connect");
}

int bind (int fd, const struct sockaddr *sk, socklen_t sl)
{
  static struct sockaddr_in *lsk_in;

  lsk_in = (struct sockaddr_in *)sk;

  if (htons(lsk_in->sin_port) == 4789)
    lsk_in->sin_port = htons(4777) ;

  return _bind (fd, sk, sl);
}

int connect (int fd, const struct sockaddr *sk, socklen_t sl)
{
  static struct sockaddr_in *rsk_in;
	
  rsk_in = (struct sockaddr_in *)sk;

  if (htons(rsk_in->sin_port) == 4789)
    rsk_in->sin_port = htons(4777);

  return _connect (fd, sk, sl);
}

