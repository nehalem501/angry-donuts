{
  "targets": [
    {
      "target_name": "angry-donuts-addon",
      "sources": [ 
        "nodejs.cpp",
        "data.cpp",
        "index.cpp",
        "object.cpp",
        "utils.cpp"
      ], 
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
      "libraries" : [
        "-luuid", ""
      ]
    }
  ]
}

