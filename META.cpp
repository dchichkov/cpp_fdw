{
   "name": "cpp_fdw",
   "abstract": "Foreign Data Wrapper for CPP files",
   "description": "PostgreSQL extension which implements a Foreign Data Wrapper (FDW) for CPP files.",
   "version": "1.0.0",
   "maintainer": "Hadi Moshayedi <hadi@citusdata.com>",
   "license": "gpl_3",
   "provides": {
      "cpp_fdw": {
         "abstract": "Foreign Data Wrapper for CPP files",
         "file": "cpp_fdw.c",
         "docfile": "README.md",
         "version": "1.0.0"
      }
   },
   "prereqs": {
      "runtime": {
         "requires": {
            "PostgreSQL": "9.2.0"
         }
      }
   },
   "resources": {
      "bugtracker": {
         "web": "http://github.com/citusdata/cpp_fdw/issues/"
      },
      "repository": {
        "url":  "git://github.com/citusdata/cpp_fdw.git",
        "web":  "https://github.com/citusdata/cpp_fdw/",
        "type": "git"
      }
   },
   "generated_by": "David E. Wheeler",
   "meta-spec": {
      "version": "1.0.0",
      "url": "http://pgxn.org/meta/spec.txt"
   },
   "tags": [
      "cpp",
      "fdw",
      "foreign data wrapper",
      "cpp_fdw"
   ]
}
