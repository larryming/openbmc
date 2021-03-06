# Copyright 2004-present Facebook. All Rights Reserved.

import unittest
import os
import sys
import inspect
import logging
import time
import traceback

from contextlib import contextmanager
from StringIO import StringIO

# Inorder for unittests to know the location of bios-util here is way for it.
# Ideally if yocto has a framework to integrate these unit tests this wouldnt
# be needed.
cmd_folder = (os.path.realpath(os.path.abspath(os.path.split(
    inspect.getfile(inspect.currentframe()))[0]))).rstrip("_test")
if cmd_folder not in sys.path:
    sys.path.insert(0, cmd_folder)


@contextmanager
def captured_output():
 new_out, nwe_err = StringIO(), StringIO()
 old_out, old_err = sys.stdout, sys.stderr
 try:
    sys.stdout, sys.stderr = new_out, nwe_err
    yield sys.stdout, sys.stderr
 finally:
    sys.stdout, sys.stderr = old_out, old_err


class Result(unittest.TestResult):

    def startTest(self, test):
        self.startTime = time.time()
        super(Result, self).startTest(test)

    def addSuccess(self, test):
        elapsed = time.time() - self.startTime
        super(Result, self).addSuccess(test)
        print(('\033[32mPASS\033[0m %s (%.3fs)' % (test.id(), elapsed)))

    def addSkip(self, test, reason):
        elapsed = time.time() - self.startTime
        super(Result, self).addSkip(test, reason)
        print(('\033[33mSKIP\033[0m %s (%.3fs) %s' %
              (test.id(), elapsed, reason)))

    def addExpectedFailure(self, test, err):
        elapsed = time.time() - self.startTime
        super(Result, self).addExpectedFailure(test, err)
        print(('\033[33mSKIP(ExpectedFailure)\033[0m %s (%.3fs) %s' %
              (test.id(), elapsed, err)))

    def __printFail(self, test, err):
        elapsed = time.time() - self.startTime
        t, val, trace = err
        print(('\033[31mFAIL\033[0m %s (%.3fs)\n%s' % (
            test.id(),
            elapsed,
            ''.join(traceback.format_exception(t, val, trace)))))

    def addFailure(self, test, err):
        self.__printFail(test, err)
        super(Result, self).addFailure(test, err)

    def addError(self, test, err):
        self.__printFail(test, err)
        super(Result, self).addError(test, err)
