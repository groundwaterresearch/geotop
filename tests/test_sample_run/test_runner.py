#!/usr/bin/env python
# -*- coding: utf-8 -*-#
# @(#)test_runner.py
#
#
# Copyright (C) 2013, GC3, University of Zurich. All rights reserved.
#
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
"""
This script will create one test for each directory containing a
``geotop.inpts`` file, will run geotop inside that directory and will
check the output files against the files contained in the ``results``
subdirectory.

Specifically, each test run on a TEST_DIR subdirectory will pass if
and only if:

* TEST_DIR/_SUCCESSFUL_RUN exists and is a file

* for each OUTPUTDIR in TEST_DIR/results:
    for each FILE in OUTPUTDIR:
      - TEST_DIR/OUTPUTDIR/FILE exists and is a file
      - TEST_DIR/OUTPUTDIR/FILE is equal to TEST_DIR/results/OUTPUTDIR/FILE

Adding a new test should be as easy as:

* adding a directory with input files for geotop

* adding a subdirectory ``results`` containing the correct output
  files generated by geotop.

"""

__author__ = 'Antonio Messina <antonio.s.messina@gmail.com>'
__docformat__ = 'reStructuredText'

import filecmp
import os
import subprocess
import shutil
import sys
import tempfile

from nose.tools import assert_equal, assert_true

def assert_is_file(fname, msg=None):
    assert os.path.isfile(fname), msg or "%s is not a file" % fname

# Directory containing this file
TESTDIR = os.path.abspath(os.path.dirname(__file__))

# Path to the geotop binary
GEOTOP = os.path.abspath(os.path.join(
    os.path.dirname(__file__), '../../GEOtop_4'))


class TestValidRun(object):
    def setUp(self):
        os.chdir(TESTDIR)

    def compare_files(self, fpath_ok, fpath_new):
        """
        Compare the *content* of two files.

        Current implementation only check that they are *exactly* the
        same files. Future implementations will also allow a numeric
        tolerance on the values, if needed.
        """
        assert_true(filecmp.cmp(fpath_ok, fpath_new))

    def _test_template(self, directory):
        """
        This template function will run geotop on a specific test
        directory, check if the `_SUCCESSFUL_RUN` is created, and
        check that all the files stored in ``results`` have been
        created by the simulation and compare them.
        """

        # Change the current working directory, because
        # ``geotop.inpts`` files usually have relative paths.
        os.chdir(directory)

        assert_is_file(GEOTOP)

        # Run geotop
        command = subprocess.Popen(
            [GEOTOP, '.'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        (stdout, stderr) = command.communicate()
        assert_equal(command.returncode, 0, msg=stderr)

        # Check that _SUCCESSFUL_RUN file exists)
        assert_is_file(os.path.join(directory, '_SUCCESSFUL_RUN'))

        resultdir = os.path.join(directory, 'results')
        if not os.path.isdir(resultdir):
            # No `results` directory. Assume it's OK.
            return

        # For each directory inside ``results``...
        for outputdir in os.listdir(resultdir):
            # and for each file in this directory...
            for fname in os.listdir(os.path.join(resultdir, outputdir)):
                # fpath_ok is the file in ``results``
                fpath_ok = os.path.join(resultdir, outputdir, fname)
                # fpath_new is the corresponding file just produced by geotop
                fpath_new = os.path.join(directory, outputdir, fname)
                # fpath_new has to exists and...
                assert_is_file(fpath_new)
                # ...it has to be equal to the file in ``results``
                self.compare_files(fpath_ok, fpath_new)

    def test_generator(self):
        for d in os.listdir(TESTDIR):
            path = os.path.join(TESTDIR, d)
            if os.path.isdir(path) and os.path.isfile(
                    os.path.join(path, 'geotop.inpts')):
                yield self._test_template, path

if __name__ == "__main__":
    import nose
    nose.run()
