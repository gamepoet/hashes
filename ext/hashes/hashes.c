/*
 Copyright (c) 2012, Ben Scott.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are
 met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/

#include <ruby.h>

extern void MurmurHash3_x86_32 (const void* key, int len, uint32_t seed, void* out);
extern uint32_t hashlittle(const void* key, size_t length, uint32_t initval);

/*----------------------------------------------------------------------------*/
static VALUE lookup3_hash(VALUE self, VALUE str, VALUE seed) {
  /* unpack args */
  uint32_t seedInt    = NUM2UINT(seed);
  const char * strPtr = RSTRING_PTR(str);
  int strLen          = RSTRING_LEN(str);

  /* hash */
  uint32_t result = hashlittle(strPtr, strLen, seedInt);
  return UINT2NUM(result);
}

/*----------------------------------------------------------------------------*/
static VALUE murmur3_hash(VALUE self, VALUE str, VALUE seed) {
  /* unpack args */
  uint32_t seedInt    = NUM2UINT(seed);
  const char * strPtr = RSTRING_PTR(str);
  int strLen          = RSTRING_LEN(str);

  /* hash */
  uint32_t result;
  MurmurHash3_x86_32(strPtr, strLen, seedInt, &result);
  return UINT2NUM(result);
}

/*----------------------------------------------------------------------------*/
void Init_hashes() {
  /* Hashes module */
  VALUE module_hashes = rb_define_module("Hashes");

  /* Hashes::Lookup3 class */
  VALUE class_lookup3 = rb_define_class_under(module_hashes, "Lookup3", rb_cObject);
  rb_define_singleton_method(class_lookup3, "hash", &lookup3_hash, 2);

  /* Hashes::Murmur3 class */
  VALUE class_murmur3 = rb_define_class_under(module_hashes, "Murmur3", rb_cObject);
  rb_define_singleton_method(class_murmur3, "hash", &murmur3_hash, 2);
}
