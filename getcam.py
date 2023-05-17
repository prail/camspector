#!/usr/bin/python3

import requests, re, sys

stream = sys.argv[1]

if stream == "1":
   STREAM_URL = "https://live.streamdays.com/vyepr4z4"
   CAM_NAME   = "pensacolachristiancollege-camp-east"
elif stream == "2":
   STREAM_URL = "https://live.streamdays.com/zy4h642p"
   CAM_NAME   = "pensacolachristiancollege-south"
elif stream == "3":
   STREAM_URL = "https://live.streamdays.com/nlp1lcbq"
   CAM_NAME   = "pensacolachristiancollege-camp-south"
elif stream == "4":
   STREAM_URL = "https://live.streamdays.com/ci7ssg3y"
   CAM_NAME   = "picci-edu-west"


needed_headers = {"referer": "https://www.pcci.edu/",
                  "User-Agent": "Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/112.0"}

#get the original iframe
req = requests.get(STREAM_URL,
                   headers=needed_headers)
                   
# get the url in the iframe
nexturl = re.search("src=\"(.+?)\"", req.content.decode("utf8")).group(1)

req2 = requests.get(nexturl,
                   headers=needed_headers)
          
          
# get the auth token from the server         
needed_headers["referer"] = nexturl         
tok = requests.get(f"{STREAM_URL}/refresh_token.text?get_param=value",
                   headers = needed_headers)
auth_token = tok.content.decode("utf8")

pl = requests.get(f"https://takeoff.jetstre.am/?account=streamdays&type=live&service=wowza&protocol=https&token={auth_token}&output=playlist.m3u8&file={CAM_NAME}")

# get the stream URL of the page
print(pl.content.decode("utf8").split("\n")[-2])
