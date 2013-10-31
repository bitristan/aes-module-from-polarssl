#!/usr/bin/env python
# -*- coding: utf-8 -*-

# decrypt_file使用，python decrypt_dir.py sourceDir dstDir [-k key]
# 将sourceDir中的文件逐一解密并放入dstDir文件夹中

import os
import sys

argc = len(sys.argv)
if argc != 3 and argc != 5:
    print 'invalid argument'
    exit()

sourceDir = sys.argv[1]
dstDir = sys.argv[2]
key = None

if argc == 5:
    key = sys.argv[4]

if not os.path.isdir(sourceDir):
    print 'invalid source directory'
    exit()

if (os.path.exists(dstDir) and os.path.isfile(dstDir)) or (not os.path.exists(dstDir)):
    os.mkdir(dstDir, 0777)

files = [ f for f in os.listdir(sourceDir)
          if os.path.isfile(os.path.join(sourceDir,f)) and not f.startswith('.') ]

for f in files:
    command = 'decrypt_file ' + sourceDir + '/' + f + ' ' + dstDir + '/' + f
    if key != None:
        command = command + ' -k ' + key
    status = os.system(command)
    if status != 0:
        command = './' + command
    status = os.system(command)
    if status == 0:
        print 'success!'
    else:
        print 'error! f=', f
