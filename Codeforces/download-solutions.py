import urllib
import json
import sys
import time, os
from bs4 import BeautifulSoup

handle = "rahulgoswami"
s = input("What's your codeforces handle?? [ENTER and skip if its me :p]\n> ")
if s:
    handle = s
MAX_SUBS = input("How many submissions do want?? [ENTER and skip for all]\n> ")
if MAX_SUBS:
    MAX_SUBS = int(MAX_SUBS)
else:
    MAX_SUBS = 1000000

DOWNLOAD_DIR = '.'
SUBMISSION_URL = 'http://codeforces.com/contest/{ContestId}/submission/{SubmissionId}'
USER_INFO_URL = 'http://codeforces.com/api/user.status?handle={handle}&from=1&count={count}'

EXT = {'C++': 'cpp', 'Python 3': 'py', 
       'PyPy 3': 'py', 'PyPy': 'py', 
       'Python': 'py', 'C': 'c', 'Java': 'java',}

replacer = {'&quot;': '\"', '&gt;': '>', '&lt;': '<', '&amp;': '&', "&apos;": "'"}
keys = replacer.keys()

def get_ext(comp_lang):
    for key in EXT.keys():
        if key.lower() in comp_lang.lower():
            return EXT[key]
    return "txt"

def parse(source_code):
    for key in keys:
        source_code = source_code.replace(key, replacer[key])
    return source_code

# base_dir = DOWNLOAD_DIR + '/' + handle
base_dir = DOWNLOAD_DIR
if not os.path.exists(base_dir):
    print(base_dir, "does not exists")
    exit(1)
    os.makedirs(base_dir)
os.chdir(base_dir)

user_info_full_url = USER_INFO_URL.format(handle=handle, count=MAX_SUBS)
print('Fetching user status:', user_info_full_url)
dic = json.loads(urllib.request.urlopen(user_info_full_url).read())
if dic['status'] != u'OK':
    print("Couldn't fetch user status")
    exit(1)

submissions = [submission for submission in dic['result'] if submission['verdict'] == u'OK']
print('Fetching %d submissions' % len(submissions))

start_time = time.time()
cnt = 0
for submission in submissions:
    con_id, sub_id = submission['contestId'], submission['id'],
    prob_name, prob_id = submission['problem']['name'], submission['problem']['index']
    comp_lang = submission['programmingLanguage']
    
    ext = get_ext(comp_lang)
    prob_name = prob_name.replace(" ", "_")
    file_name = "{:04d}{}_({}).{}".format(con_id, prob_id, prob_name, ext)
    if os.path.exists(file_name):
        print("[INFO] already have {}".format(file_name))
        continue
    
    submission_full_url = SUBMISSION_URL.format(ContestId=con_id, SubmissionId=sub_id)
    print("Fetching submission:", submission_full_url)
    submission_info = urllib.request.urlopen(submission_full_url).read()
    soup = BeautifulSoup(submission_info, 'html.parser')
    submission_text = soup.find('pre', id='program-source-text')
    if submission_text is None:
        print("Could not fetch solution", sub_id)
        continue
    result = submission_text.text.replace('\r', '')
    if ext == "txt": 
        print(comp_lang, "language extension not found")
    file = open(file_name, 'w')
    file.write(result)
    file.close()
    print("[INFO] saved as {}".format(file_name))
    cnt += 1

end_time = time.time()
duration_secs = int(end_time - start_time)
print("\n{} new files!".format(cnt))
print("Finished in %d minutes %d seconds" % (duration_secs / 60, duration_secs % 60))
