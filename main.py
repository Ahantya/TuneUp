import spotipy
from spotipy.oauth2 import SpotifyClientCredentials
import os
import sys

# Get user input
answer = input("Do you want to open TuneUp? (yes/no): ")
if (answer == "no" or answer == "n"):
	sys.exit("Bye Bye! Ignore error below")
returning = input("Are you a returning user? (yes/no): ")
if (returning.lower() == 'no'):
	os.system("g++ user.cpp -o user && ./user")
else:
    enter = input("Enter your username: ")
    username_exists = False
    usernames_passwords = {}

    with open("userssofar.txt", "r") as file:
        for line in file:
            line = line.strip()
            if line.lower().startswith("username: "):
                username = line.split("Username: ")[1].strip().lower()
            elif line.lower().startswith("password: "):
                password = line.split("Password: ")[1].strip().lower()
                usernames_passwords[username] = password

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


skip = input("Do you want to skip the data process? (yes/no): ")
if skip.lower() == 'yes':
    os.system("g++ main.cpp -o main && ./main")
    sys.exit("Bye Bye! Ignore error below")
print()
rewrite_option = input("Do you want to rewrite over your data? (yes/no): ")
file_mode = 'w' if rewrite_option.lower() == 'yes' else 'a'


# Execute the command in the shell

# Replace these with your own credentials
client_id = '4fe326301d5842369470c275f63941c6'
client_secret = '5d953feeaed1436c9c518ae13eddf49a'
sys.stderr = open(os.devnull, 'w')

print()
# Specify a cache file path
cache_path = 'cache.txt'

# Create a Spotify client with caching enabled
client_credentials_manager = SpotifyClientCredentials(client_id, client_secret)
spotify = spotipy.Spotify(client_credentials_manager=client_credentials_manager)

# Specify the user's Spotify username
username = input('Enter your Spotify Username: ')

# Get the user's playlists


playlists = spotify.user_playlists(username)


if (answer == "yes" or answer == "y" or answer == "yeah"):
	os.system("g++ main.cpp -o main && ./main")


# Set the initial offset to 0
offset = 0

def show_tracks(playlist_id, file):
    results = spotify.user_playlist(username, playlist_id)
    for i in results['tracks']['items']:
        song_name = i['track']['name']
        song_artist = i

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
        song_features = get_features(i['track']['id'])
        if song_features:
            playlist_avg_features['danceability'] += song_features['danceability']
            playlist_avg_features['energy'] += song_features['energy']
            playlist_avg_features['loudness'] += song_features['loudness']
            playlist_avg_features['acousticness'] += song_features['acousticness']
            playlist_avg_features['instrumentalness'] += song_features['instrumentalness']
            playlist_avg_features['liveness'] += song_features['liveness']
            playlist_avg_features['valence'] += song_features['valence']
            playlist_avg_features['tempo'] += song_features['tempo']
    playlist_avg_features = {k: round(v / song_total, 4) for k, v in playlist_avg_features.items()}
    features_str = " ".join(f'{key}: {value}' for key, value in playlist_avg_features.items())
    return features_str



with open('playlist_average_features.txt', file_mode) as file:
    playlists = spotify.user_playlists(username)
    for playlist in playlists['items']:      
        playlist_name = playlist['name']
        file.write(f'Playlist: {playlist_name}\n')
        # Get the ID of the current playlist
        playlist_id = playlist['id']
        this_features = get_playlist_avg_features(playlist_id)
        file.write(this_features + '\n')
        show_tracks(playlist)
    file.close()
