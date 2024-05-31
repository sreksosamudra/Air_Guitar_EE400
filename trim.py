import wave
import numpy as np

def trim_wav(file_path, start_sec, end_sec, output_path):
    """
    Trims a WAV file from start_sec to end_sec and saves the result to a new file.

    Args:
    file_path (str): The path to the original WAV file.
    start_sec (float): The start time in seconds for the trim.
    end_sec (float): The end time in seconds for the trim.
    output_path (str): The path where the trimmed WAV file should be saved.
    """
    with wave.open(file_path, 'rb') as wav:
        # Get file parameters
        n_channels, sampwidth, framerate, n_frames, comptype, compname = wav.getparams()
        
        # Calculate the start and end frame
        start_frame = int(start_sec * framerate)
        end_frame = int(end_sec * framerate)
        
        # Set position and read frames
        wav.setpos(start_frame)
        frames = wav.readframes(end_frame - start_frame)

        # Convert frames to numpy array for manipulation if needed
        audio = np.frombuffer(frames, dtype=np.int16)

    # Save the trimmed audio
    with wave.open(output_path, 'wb') as output:
        output.setparams((n_channels, sampwidth, framerate, 0, comptype, compname))
        output.writeframes(audio.tobytes())

# Example usage
trim_wav("./chord_recordings/G.wav", 0.3, 2.3, "trimmed_G.wav")
