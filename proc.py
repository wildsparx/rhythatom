#!/usr/bin/python2

# Copyright (C) 2017 Asher Blum
# Script to assemble HTML/js into one file

import re
import json
import sys

def parse_include(inc):
  if not ' ' in inc:
    return (inc, {})
  fn, args = inc.split(' ', 1)
  try:
    return (fn, json.loads('{%s}' % args))
  except:
    print "Error parsing json: %r" % args
    raise

def interpolate_args(page, args):
  for k, v in sorted(args.items()):
    pat = r'\$%s(?=\W)' % k
    # sys.stderr.write("replacing %r -> %r\n" % (pat, str(v)))
    page = re.sub(pat, str(v), page)
  return page

def include_one(page):
  #sys.stderr.write("include_one:\n")
  m = re.search(r'\n@include\((.+?)\)', page)
  if not m:
    return None
  all_args = m.group(1)
  fn, args = parse_include(all_args)
  spage = open(fn).read()
  spage = interpolate_args(spage, args)
  return page.replace('\n@include(%s)' % all_args, "\n" + spage)

def include_all(page):
  while True:
    p2 = include_one(page)
    if not p2:
      return page
    page = p2

def main(src_fn, dest_fn):
  page = open(src_fn).read()
  page = include_all(page)
  open(dest_fn, 'w').write(page)

if __name__ == '__main__':
  main(sys.argv[1], sys.argv[2])
