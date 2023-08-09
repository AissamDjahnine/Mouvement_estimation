# Optical Flow Estimation with Horn-Schunck Method and Multi-Resolution
Experience Horn and Schunck's groundbreaking work, the first variational method for optical flow estimation. Our project implements their method and introduces a multi-resolution strategy to handle larger displacements. By assuming constant pixel intensities over time, we derive the optical flow equation. While effective for small motions, this method struggles with larger displacements due to image gradient issues. Our approach involves a smoothness constraint and a multi-scale pyramid of downsampled images for robust optical flow estimation.

## Usage :
Inputs : Image 1 & Image 2 ( un mouvement elementaire ) 
# Image 1
![alt text](https://github.com/AissamDjahnine/Mouvement_estimation/blob/master/image1.bmp)
# Image 2
![alt text](https://github.com/AissamDjahnine/Mouvement_estimation/blob/master/image2.bmp)
# Resultats (via quiver pythonb) : 
![alt text](https://github.com/AissamDjahnine/Mouvement_estimation/blob/master/resultats.png)




