import os
import binascii
import sys
from subprocess import call

from struct import pack

crash = 0
count = 1
cursor = 0
prog_name = "a.out"
opcodes = []
header_info = []
mal = "4831C09090"

def little_endian(str):
    i = len(str) - 1
    p = ""
    while (i >= 0):
        p += chr(int(str[i - 1] + str[i], 16))
        i -= 2
    return (p)

def print_header(one, buff):
        print '\033[1m------------ \033[32mTARGET CODE\033[0;1m ------------'
        print '|        \033[1;33mcall _malloc - \033[1;32m' + str(count) + ' of '\
                + str(len(opcodes)) + '\033[0m      \033[1m|'
        print '| ... ' + buff[cursor - 38:cursor - 9] + ' |'
        print '| ' + buff[cursor - 9:cursor] + '\033[1;32m[' + one \
                + ']\033[0;1m' + buff[cursor+len(one):cursor + len(one) + 12] + ' \033[1m|'
        print '| ' + buff[cursor + len(one) + 12:cursor + 51] + ' ... |'
	print '| \033[1;32m[call _malloc] ' + one[:2] + ' ' + one[2:4] + ' ' \
		+ one[4:6] + ' ' + one[6:8] + ' ' + one[8:10] + '\033[0;1m     |'
        print '-------------------------------------'

def print_injection(one, buff):
        print '\033[1m----------- \033[31mPOISONED CODE\033[0;1m -----------'
	print '|        \033[1;33mcall _malloc - \033[1;32m' + str(count) + ' of '\
                + str(len(opcodes)) + '\033[0m      \033[1m|'
        print '| ... ' + buff[cursor - 38:cursor - 9] + ' |'
        print '| ' + buff[cursor - 9:cursor] + '\033[1;31m[' + mal[:-4] \
                + '][90][90]\033[0;1m' + buff[cursor+len(one):cursor + len(one) + 8] + ' \033[1m|'
        print '| ' + buff[cursor + len(one) + 8:cursor + 47] + ' ... |'
	print '| \033[1;31m+ [xor rax, rax] 48 31 C0\033[0;1m         |'
	print '| \033[1;31m+ [nop]          90\033[0;1m               |'
	print '| \033[1;31m+ [nop]          90\033[0;1m               |'
	print '| \033[1;32m- [call _malloc] ' + one[:2] + ' ' + one[2:4] + ' ' \
		+ one[4:6] + ' ' + one[6:8] + ' ' + one[8:10] + '\033[0;1m   |'
        print '-------------------------------------'


def poison(buff, one):
        return (buff[:cursor] + mal + buff[cursor + len(one):])

def check_size(buff):
        a = buff[432:432 + 16]
        return (a)

def make_a_mess(one):
        global cursor
        with open(prog_name, "rb") as f:
                content = f.read()
                f.close()
        buff = binascii.hexlify(content)
        cursor = buff.find(one)
        print_header(one, buff)
        a = int((little_endian(check_size(buff))).encode('hex'), 16)
	print '\033[1;33m-> Valid malloc call : \033[1;32mOK'
	print '\033[1;33m-> Size of .text section : \033[1;32m' + str(a) + ' bytes'
	print '\033[1;33m-> Infection possible : \033[1;32mYES'
        print '\033[1;33m-> Poisoning malloc \'' + one + '\' ...\n\033[0m'
        buff = poison(buff, one)
        print_injection(one, buff)
	new_name = prog_name + ".infected"
        with open(new_name, "w+") as f:
                f.write(binascii.unhexlify(buff))
                f.close()
	os.chmod(new_name, 0777)
	print '\t\033[1;33m>> ' + prog_name + '.infected' + ' <<'
        print '\t\033[1;32m >> ENTER TO RUN <<\033[0m'
        raw_input("")
	print '\033[0;33m-> Running ' + new_name + ' with vulnerable code...\n'
	if len(sys.argv) > 2:
		args = sys.argv[2].split()
	al = []
	al.append("./" + new_name)
	if len(sys.argv) > 2:
		for el in args:
			al.append(el)
	rc = call(al)
	print '\033[1;33mCRASH : ' + ("\033[1;32mNO" if rc == 0 or rc == 1 else "\033[1;31mYES")
	if rc != 0 and rc != 1:
		global crash
		crash += 1
	if rc == -11:
		print '\033[0;31m(SEGFAULT)'
	print '\033[1;32mcrash count : \033[0;32m' + str(crash) + '/' + str(len(opcodes))
	print '\033[0m'
        raw_input("")

def read_n_convert():
    for one in opcodes:
        	os.system('clear')
                make_a_mess(one)
		global count
		count += 1

def get_opcodes(valid):
        global opcodes
        for elem in valid:
                s = elem.split()
                opcodes.append(s[1] + s[2] + s[3] + s[4] + s[5])

def get_symbols():
        valid = []
        if len(sys.argv) >= 2:
                global prog_name
                prog_name = sys.argv[1]
        os.system("/usr/bin/otool -tVj " + prog_name + " | grep malloc > .sym_logs")
        with open(".sym_logs", "r") as fo:
            for line in fo:
                    splitted = line.split()
                    for elem in splitted:
                        if elem == "_malloc":
                            valid.append(line)
        get_opcodes(valid)

def main():
        get_symbols()
        read_n_convert()

if __name__ == '__main__':
    main()
