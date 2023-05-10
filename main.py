import spotipy
from spotipy.oauth2 import SpotifyClientCredentials
import os
import sys

# Get user input
answer = input("Do you want to open TuneUp? (yes/no): ")
if (answer == "no" or answer == "n"):
	sys.exit("Bye Bye! Ignore error below")
print()
skip = input("Do you want to skip the data process? (yes/no): ")
if answer.lower() in ["yes", "y"]:
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

playlists = spotify.user_playlists(username)

with open('playlist_genres.txt', file_mode) as f:
    # Loop through all the playlists
    for playlist in playlists['items']:
        playlist_name = playlist['name']
        f.write(f'Playlist: {playlist_name}\n')
        # Get the ID of the current playlist
        playlist_id = playlist['id']
        # Get the tracks from the current playlist
        results = spotify.user_playlist(username, playlist_id)
        tracks = results['tracks']
        show_tracks(tracks, f)
        while tracks['next']:
            tracks = spotify.next(tracks)
            show_tracks(tracks, f)

# with open('playlist_genres.txt', 'a') as f:
#     trackList = get_playlist_track_id(username, playlist_id)
#     for track in trackList:
#         f.write(f'{track}\n')
#to append instead of restarting file

if (answer == "yes" or answer == "y" or answer == "yeah"):
	os.system("g++ main.cpp -o main && ./main")

min_listeners = 100000

# Create an empty list to store the results
all_artists = []

# Set the initial offset to 0
offset = 0

# Loop through the results, adding each artist to the list
# while True:
#     results = spotify.search(q='genre:hyperpop year:2022', type='artist', offset=offset)
#     items = results['artists']['items']
#     if len(items) == 0:
#         # We've reached the end of the results
#         break
#     for item in items:
#         if item['followers']['total'] > min_listeners:
#             all_artists.append(item['name'])
#             if len(all_artists) >= 50:
#                 break
#     if len(all_artists) >= 50:
#         break
#     offset = offset + len(items)

# # Write the list of all artists with over 100000 monthly listeners in the hyperpop genre to a file
# with open("related_artists.txt", "a") as file:
#     for artist in all_artists:
#         file.write(artist + "\n")