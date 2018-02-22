import pprint
import pickle

pkl_file = open('00.pkl', 'rb')

data1 = pickle.load(pkl_file)
pprint.pprint(data1)

pkl_file.close()
