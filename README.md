# Raster Image Viewer and Editor (Console Application)

## Project Description
This project is a console-based raster image editor. It supports loading, processing, transforming, and saving raster images through user sessions.

## Supported Image Formats
- PBM, PGM, PPM, BMP

## Application Workflow

### Sessions
- The application starts without any loaded files or sessions.
- Use the `load` command to start a new session with one or more image files.
- Each session receives an unique ID (a whole positive number) to allow managing multiple sessions.
  
- Transformations apply to **all images** loaded in the current session.

### Commands and Features

- **Convert to Grayscale**  
  `grayscale`  
  Converts all color images in the current session to grayscale. Already grayscale images remain unchanged.

- **Convert to Monochrome (Black and White)**  
  `monochrome`  
  Converts all images to strictly black and white pixels (no gray shades). Monochrome images remain unchanged.

- **Negative**  
  `negative`  
  Creates a negative (inverted tones) of all images in the current session.

- **Rotate and Flip Images**  
  `rotate left` / `rotate right` / `flip top` / `flip left`  
  Performs rotation or mirror transformations.

- **Undo Last Transformation**  
  `undo`  
  Reverts the last transformation applied in the current session. Has no effect if no transformations have been made.

- **Redo Last Undo**  
  `redo`  
  Reapplies the last undone transformation, if any.

- **Add Image to Current Session**  
  `add image02.ppm`  
  Adds a new image to the session. Previous transformations are **not** applied to this new image.

- **Save Changes**  
  `save`  
  Saves transformed images with a timestamp appended to the filename. Undo operations still work after saving and does not delete the saved files.

- **Save As**  
  `saveas newName1 newName2 ...`  
  Saves transformed images using the specified filenames. If fewer names are provided than images, default names (with timestamps) are used for the rest.

- **Session Info**  
  `list session`  
  Displays the current session’s ID and the images loaded, including their names and formats.

- **Paste Image**  
  `paste image_src image_dest posX posY`  
  Inserts pixels from `image_src` into `image_dest` starting at position `(posX, posY)`. The destination image expands if needed, and empty pixels are white.
  
- **Switch Between Sessions**  
  `switch <session_id>`  
  Changes the active session to the specified ID.

- **Exit Application**  
  `exit`  
  Exits the editor. If there are sessions with unsaved transformations, ask the user to save them before exiting.
