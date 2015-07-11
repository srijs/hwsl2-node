{
  "targets": [
    {
      "target_name": "hwsl2",
      "sources": [
        "hwsl2.c",
        "addon.cc"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"],
      "cflags_c": ["-mavx2", "-msse2", "-msse4.1", "-mpclmul", "-O3", "-Wno-ignored-qualifiers"],
      'xcode_settings': {
        'OTHER_CFLAGS': [
          "-mavx2", "-msse2", "-msse4.1", "-mpclmul", "-O3", "-Wno-ignored-qualifiers"
        ],
      },
    }
  ]
}
