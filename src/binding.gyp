{
  "targets": [
    {
      "target_name": "angry-donuts-addon",
      "sources": [ "nodejs.cpp" ], 
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}

