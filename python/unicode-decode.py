#!/usr/bin/python
# -*- coding: utf8 -*-

msg = u'今天天氣真好'
encoded = msg.encode('utf8')
print 'utf8: ' + encoded
print 'repr: ' + repr(encoded)

encoded = '\xe4\xbb\x8a\xe5\xa4\xa9\xe5\xa4\xa9\xe6\xb0\xa3\xe7\x9c\x9f\xe5\xa5\xbd'
msg = encoded.decode('utf-8')
print "decode('utf-8'): " + msg

# convert encoded string to an int list
bytes = [ int('0x' + elem.encode("hex"), 16) for elem in encoded]
print 'byte list: ',
print bytes

# convert it to byte array
print "bytearray: [",
bytes = bytearray(encoded, 'hex')
for b in bytes:
    print "%#x," % b,
print ']'

bytes = bytearray.fromhex('e4 bb 8a e5 a4 a9 e5 a4 a9 e6 b0 a3 e7 9c 9f e5 a5 bd')
print 'bytes: ' + bytes

import array
ary = array.array('B', [0xe4, 0xbb, 0x8a, 0xe5, 0xa4, 0xa9, 0xe5, 0xa4, 0xa9, 0xe6, 0xb0, 0xa3, 0xe7, 0x9c, 0x9f, 0xe5, 0xa5, 0xbd])
print 'array: ' + str(ary)
print 'array.tostring(): ' + ary.tostring()


################################################################################
print("--------------------------------------------------------")


msg = u'今天天氣真好'
encoded = msg.encode('utf-16')
print 'utf16: ' + encoded
print 'repr: ' + repr(encoded)

encoded = '\xff\xfe\xcaN)Y)Y#l\x1fw}Y'
msg = encoded.decode('utf-16')
print "decode('utf-16'): " + msg

# convert it to byte array
print "bytearray: [",
bytes = bytearray(encoded, 'hex')
for b in bytes:
    print "%#x," % b,
print ']'

bytes = bytearray.fromhex('ff fe ca 4e 29 59 29 59 23 6c 1f 77 7d 59')
print "bytes.decode('utf-16'): " + bytes.decode('utf-16')

bytes = bytearray([ 0xff, 0xfe, 0xca, 0x4e, 0x29, 0x59, 0x29, 0x59, 0x23, 0x6c, 0x1f, 0x77, 0x7d, 0x59, ])
print "bytes.decode('utf-16'): " + bytes.decode('utf-16')

import array
ary = array.array('B', [ 0xff, 0xfe, 0xca, 0x4e, 0x29, 0x59, 0x29, 0x59, 0x23, 0x6c, 0x1f, 0x77, 0x7d, 0x59, ])
print 'array: ' + str(ary)
print 'array.tostring(): ' + ary.tostring()
print "array.tostring().decode('utf-16'): " + ary.tostring().decode('utf-16')

