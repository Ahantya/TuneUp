import spotipy
from spotipy.oauth2 import SpotifyClientCredentials
import os
import sys

# Get user input
answer = input("Do you want to open TuneUp ")

# Execute the command in the shell

# Replace these with your own credentials
client_id = 'f8d8565044e0413ea42506fc67003061'
client_secret = '8d7d14da14d3430b8e74e034930b7b36'
sys.stderr = open(os.devnull, 'w')

if (answer == "no" or answer == "n"):
	1/0

print()
print("Gathering Data")
# Specify a cache file path
cache_path = 'cache.txt'

# Create a Spotify client with caching enabled
client_credentials_manager = SpotifyClientCredentials(client_id, client_secret)
spotify = spotipy.Spotify(client_credentials_manager=client_credentials_manager)

# Specify the user's Spotify username
username = input('Enter your Spotify Username')

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
#user = spotify.user(username)
#print(artist_related_artists('5K4W6rqBFWDnAN6FQUkS6x'))
#

# def artist_related_artists(self, artist_id):
#         """ Get Spotify catalog information about artists similar to an
#             identified artist. Similarity is based on analysis of the
#             Spotify community's listening history.

#             Parameters:
#                 - artist_id - the artist ID, URI or URL
#         """
#         trid = self._get_id("artist", artist_id)
#         return self._get("artists/" + trid + "/related-artists")
  
with open('user_info.txt', 'a') as q:
  list = artist_related_artist('2YOYua8FpudSEiB9s88IgQ')
  for artist in list:
    q.write(artist + '\n')

with open('playlist_genres.txt', 'a') as f:
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
#if (answer == "yes" or answer == "y" or answer == "yeah"):
#	os.system("g++ main.cpp -o main && ./main")

min_listeners = 100000

# Create an empty list to store the results
all_artists = []

# Set the initial offset to 0
offset = 0

# Loop through the results, adding each artist to the list
while True:
    results = spotify.search(q='genre:hyperpop year:2022', type='artist', offset=offset)
    items = results['artists']['items']
    if len(items) == 0:
        # We've reached the end of the results
        break
    for item in items:
        if item['followers']['total'] > min_listeners:
            all_artists.append(item['name'])
            if len(all_artists) >= 50:
                break
    if len(all_artists) >= 50:
        break
    offset = offset + len(items)

# Write the list of all artists with over 100000 monthly listeners in the hyperpop genre to a file
with open("related_artists.txt", "a") as file:
    for artist in all_artists:
        file.write(artist + "\n")