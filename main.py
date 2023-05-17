import spotipy
from spotipy.oauth2 import SpotifyClientCredentials
import os
import sys

# Get user input
file_mode = 'w'
username = ""
answer = input("Do you want to open TuneUp? (yes/no): ")
if (answer == "no" or answer == "n"):
	sys.exit("Bye Bye! Ignore error below")
while (answer != 'yes'): 
  print ('Error. Please enter \'yes\' or \'no\'')
  answer = input("Do you want to open TuneUp? (yes/no): ")

returning = input("Are you a returning user? (yes/no): ")
if (returning.lower() == 'no'):
	os.system("g++ user.cpp -o user && ./user")
enter = input("Enter your username: ")
username_exists = False
usernames_passwords = {}
usernames_levels = {}
with open("userssofar.txt", "r") as file:
    for line in file:
        line = line.strip()
        if line.lower().startswith("username: "):
            username = line.split("Username: ")[1].strip().lower()
            if username not in usernames_passwords:
                usernames_passwords[username] = None
            if username not in usernames_levels:
                usernames_levels[username] = None
        elif line.lower().startswith("password: "):
            password = line.split("Password: ")[1].strip().lower()
            if username in usernames_passwords:
                usernames_passwords[username] = password
        elif line.lower().startswith("level: "):
            level = line.split("Level: ")[1].strip().lower()
            if username in usernames_levels:
                usernames_levels[username] = level

while not username_exists:
    if enter.lower() in usernames_passwords:
        username_exists = True
    else:
        enter = input("Enter your username CORRECTLY: ")

enter_password = input("Enter your password: ")
password_correct = False

while not password_correct:
    if enter_password.lower() == usernames_passwords[enter.lower()]:
        password_correct = True
    else:
        enter_password = input("Enter your password CORRECTLY: ")

print("Welcome to TuneUp. We analyze your music to help you get recommended music without having to search manually! As you use the app more and more, you will level up and get an ability to request more songs that are recommended by us!")

client_id = '4fe326301d5842369470c275f63941c6'
client_secret = '5d953feeaed1436c9c518ae13eddf49a'
sys.stderr = open(os.devnull, 'w')

print()
# Specify a cache file path
cache_path = 'cache.txt'

# Create a Spotify client with caching enabled
client_credentials_manager = SpotifyClientCredentials(client_id, client_secret)
spotify = spotipy.Spotify(client_credentials_manager=client_credentials_manager)

# Get the user's playlists
username = enter;

playlists = spotify.user_playlists(username)
print("Loading Analytics of your Playlist(s)\n")

# Set the initial offset to 0
offset = 0

def get_features(track_id: str) -> dict:   
    try:
        features = spotify.audio_features([track_id])
        if features:
            return {
                'danceability': features[0]['danceability'],
                'energy': features[0]['energy'],
                'loudness': features[0]['loudness'],
                'acousticness': features[0]['acousticness'],
                'instrumentalness': features[0]['instrumentalness'],
                'liveness': features[0]['liveness'],
                'valence': features[0]['valence'],
                'tempo': features[0]['tempo']
            }
    except:
        return None
			
def get_playlist_avg_features(playlist_id: str) -> str:
    playlist_avg_features = {'danceability': 0.0, 'energy': 0.0, 'loudness': 0.0, 'acousticness': 0.0, 'instrumentalness': 0.0, 'liveness': 0.0, 'valence': 0.0, 'tempo': 0.0}
    results = spotify.user_playlist(username, playlist_id)
    song_total = 0
    for i in results['tracks']['items']:
        song_total += 1
        if i is not None and 'track' in i and i['track'] is not None:
            if 'id' in i['track']:
                song_features = get_features(i['track']['id'])
                # Process song_features and update playlist_avg_features
            else:
                print("")
        else:
            print("")


        if song_features:
            playlist_avg_features['danceability'] += song_features['danceability']
            playlist_avg_features['energy'] += song_features['energy']
            playlist_avg_features['loudness'] += song_features['loudness']
            playlist_avg_features['acousticness'] += song_features['acousticness']
            playlist_avg_features['instrumentalness'] += song_features['instrumentalness']
            playlist_avg_features['liveness'] += song_features['liveness']
            playlist_avg_features['valence'] += song_features['valence']
            playlist_avg_features['tempo'] += song_features['tempo']
    if song_total != 0:
        playlist_avg_features = {k: round(v / song_total, 4) for k, v in playlist_avg_features.items()}
        features_str = " ".join(f'{key}: {value}' for key, value in playlist_avg_features.items())
        return features_str

with open('playlist_all_features.txt', file_mode) as file:
    file.write("\n")
    playlists = spotify.user_playlists(username)
    for playlist in playlists['items']:
        results = spotify.user_playlist(username, playlist['id'])
        print()
        print(playlist['name'])
        if results['tracks']['items']:
            track_id = results['tracks']['items'][0]['track']['id']
            print(get_features(track_id))
        else:
            print("No tracks found in the results.")
        print()
        for i in results['tracks']['items']:
            if 'track' in i and i['track'] is not None:
                if 'id' in i['track']:
                    song_features = get_features(i['track']['id'])
                    track_name = i['track']['name'] if i['track'].get('name') else ""
                    if song_features is not None:
                        features = (
                            str(song_features['danceability']) + ", " +
                            str(song_features['energy']) + ", 0, " +
                            str(song_features["loudness"]) + ", 0, 0, " +
                            str(song_features["acousticness"]) + ", " +
                            str(song_features["instrumentalness"]) + ", " +
                            str(song_features["liveness"]) + ", " +
                            str(song_features["valence"]) + ", " +
                            track_name + ", ,"
                        )
                        file.write(features + '\n')
    file.close()
	
with open('playlist_average_features.txt', 'a') as file:
    playlists = spotify.user_playlists(username)
    for playlist in playlists['items']:      
        playlist_name = playlist['name']
        #print(playlist_name)
        file.write(f'Playlist: {playlist_name}\n')
        # Get the ID of the current playlist
        playlist_id = playlist['id']
			
        this_features = get_playlist_avg_features(playlist_id)
        if this_features is not None:
            file.write(this_features + '\n')
        #show_tracks(playlist)
    file.close()

os.system(f"g++ add.cpp -o add && ./add {username}")

while True:
  choice = input("1: Song of the Day!\n2: get new songs for your playlist!\n3: view profile!\n4: Help\n5: close TuneUp\n")
  match choice:
    case "1": #sotd
      os.system("g++ sotd.cpp -o sotd && ./sotd")
    case "2": #new songs for playlist
      print('Your available playlists: (If you do not see one of your playlists below, you must make it public and add it to your profile so TuneUp can access it.)')
      playlists = spotify.user_playlists(username)
      for index, playlist in enumerate(playlists['items'], 1):
        playlist_name = playlist['name']
        print(f"{index}: {playlist_name}")
        print()
      which_song = input('Which playlist would you like to add songs to?\n')
      #os.system(f"g++ main.cpp -o main && ./main {usernames_levels[username]}")
      os.system(f"g++ main.cpp -o main && ./main {usernames_levels[username]} {which_song}")
    case "3": #view profile
      os.system(f"g++ profile.cpp -o profile && ./profile {username}" )
    case "4": # help
      os.system("g++ help.cpp -o help && ./help")
    case "5": #close tuneup
   	  sys.exit("Bye Bye! Ignore error below")