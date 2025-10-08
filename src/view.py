import cv2

# Load image
img = cv2.imread("img/img.bmp")
if img is None:
    print("Failed to load image!")
    exit()

# Mouse callback: only on left click
def mouse_callback(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        b, g, r = img[y, x]  # note: img[y, x] not img[x, y]
        color_int = (r << 16) | (g << 8) | b  # convert to 0xRRGGBB
        print(f"x={x}, y={y}, BGR=({b},{g},{r}), 0xRRGGBB={hex(color_int)}")

cv2.namedWindow("image")
cv2.setMouseCallback("image", mouse_callback)

while True:
    cv2.imshow("image", img)
    key = cv2.waitKey(20) & 0xFF
    if key == 27:  # ESC to exit
        break

cv2.destroyAllWindows()
