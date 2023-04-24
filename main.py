import spotipy
from spotipy.oauth2 import SpotifyClientCredentials
import os
import sys

# Get user input
yes = input("do you want to open GrooveHub?")

# Execute the command in the shell


# Replace these with your own credentials
client_id = 'f8d8565044e0413ea42506fc67003061'
client_secret = '8d7d14da14d3430b8e74e034930b7b36'
sys.stderr = open(os.devnull, 'w')

print()
print("inputting genres!!!!")
# Specify a cache file path
cache_path = 'cache.txt'

# Create a Spotify client with caching enabled
client_credentials_manager = SpotifyClientCredentials(client_id, client_secret)
spotify = spotipy.Spotify(client_credentials_manager=client_credentials_manager)

# Specify the user's Spotify username


username = ''

# Get the user's playlists
playlists = spotify.user_playlists(username)
playlist = playlists['items'][0]
playlist_id = playlist['id']


def show_tracks(results, file):
    for i, item in enumerate(results['items']):
        track = item['track']
        artist = track['artists'][0]['name']  # Get the name of the first artist
        track_name = track['name']  # Get the name of the track
        # Get the genres for the first artist of the track
        genres = spotify.artist(track['artists'][0]['id'])['genres']
        # Write the track name, artist, and genre to a file
        file.write(f'{track_name} - {artist} ({", ".join(genres)})\n')


def get_playlist_track_id(username, playlist_id, file):
    results = spotify.user_playlist(username, playlist_id)
    tracks = results['tracks']
    show_tracks(tracks, file)
    while tracks['next']:
        tracks = spotify.next(tracks)
        show_tracks(tracks, file)


with open('playlist_genres.txt', 'w') as f:
    get_playlist_track_id(username, playlist_id, f)

# with open('playlist_genres.txt', 'a') as f:
#     trackList = get_playlist_track_id(username, playlist_id)
#     for track in trackList:
#         f.write(f'{track}\n')
#to append instead of restarting file


if (yes == "yes"):
	os.system("g++ main.cpp -o main && ./main")

# # Replace these with your own credentials
# client_id = '8e74be26b7204ad1a60540becc1bb604'
# client_secret = '9526fb2f445a490e9a9834a23ebf870b'
