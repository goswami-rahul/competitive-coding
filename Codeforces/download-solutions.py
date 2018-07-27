import urllib
import json
import sys
import time, os
from bs4 import BeautifulSoup

MAX_SUBS = 1000000
if (len(sys.argv) < 2):
    print('Usage: python main.py <handle>')
    exit(1)

handle = sys.argv[1]

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
for submission in submissions:
    con_id, sub_id = submission['contestId'], submission['id'],
    prob_name, prob_id = submission['problem']['name'], submission['problem']['index']
    comp_lang = submission['programmingLanguage']
    submission_full_url = SUBMISSION_URL.format(ContestId=con_id, SubmissionId=sub_id)
    print("Fetching submission:", submission_full_url)
    submission_info = urllib.request.urlopen(submission_full_url).read()
    soup = BeautifulSoup(submission_info, 'html.parser')
    submission_text = soup.find('pre', id='program-source-text')
    if submission_text is None:
        print("Could not fetch solution", sub_id)
        continue
    result = submission_text.text.replace('\r', '')
    ext = get_ext(comp_lang)
    new_directory = base_dir + '/' + str(con_id)
    prob_name = prob_name.replace(" ", "_")
    file_name = "{:04d}{}_({}).{}".format(con_id, prob_id, prob_name, ext)
    if ext == "txt": 
        print(comp_lang, "language extension not found")
    file = open(file_name, 'w')
    file.write(result)
    file.close()
end_time = time.time()

duration_secs = int(end_time - start_time)
print("Finished in %d minutes %d seconds" % (duration_secs / 60, duration_secs % 60))
