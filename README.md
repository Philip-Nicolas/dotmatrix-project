# dot-matrix display project

---

see the git history of this branch for step-by-step instructions



## Step 1
One shift register, 4 rows & 4 columns of the display wired up.

## Step 2
Quickly alternating pattern that cannot be drawn in just one `shiftOut`.
Use a potentiometer to vary the 'refresh rate'.

## Step 3
Both shift registers wired up, along with entire dot matrix display.
Pattern extended to whole display.

## Step 4
Add images to draw on the display.
Code binary logic to change images to bits to `shiftOut`.

## Step 5
Add animation whose frames are updated separately from display.

## Step 6
Use a timed interrupt to draw scan lines so that other code can run concurrently,
without worrying about messing up the image.
