

## Key Summary Description

* Object creation: Keys 1, 2, 3 for creating a "cube", "rabbit", "bumpy object"
* Selection: Mouse click on object for selection 
* T for delete
* P, F for phong and mirror
* 8 for shadow rotation
* B for changing shadow color between black and red
* E, R, I, O for rotating the object in 4 directions
* A, D for left right, W, S for forward backwards, Y, U for up and down translations
* G, H for scale up and down of object
* 4, 5, 6, 7, for looking around the cube
* Z, X, C, V for looking around plane



## Object Creation.


![Screen Shot 2021-11-29 at 10 18 32 PM](https://user-images.githubusercontent.com/35964921/143981027-4fb180ce-c0ef-4352-bb39-a5f4a5ae9b3d.png)




  
 ## Selection.


![Screen Shot 2021-11-29 at 11 16 32 PM](https://user-images.githubusercontent.com/35964921/143984835-0d64c209-197d-44e1-8e5b-bc4391a151df.png)

 
When clicking on the object, the object is selected. Once it is selected, the color changes to green.
  
  
 And then I could press t to delete:
 
![Screen Shot 2021-11-29 at 11 16 36 PM](https://user-images.githubusercontent.com/35964921/143984866-96d2b85d-8f9e-4171-ae94-c9d300d91643.png)





 ## Object Movement and scaling
 
 

https://user-images.githubusercontent.com/35964921/143985988-5c249ff8-95f6-4688-980e-fca3a051cf3e.mp4

Just like the previous assignment, the objects can move around. But for this one, shadows are added in and also objects could go forward and backwards.





## Shadows/Shadow control.


![Screen Shot 2021-11-29 at 10 24 10 PM](https://user-images.githubusercontent.com/35964921/143986088-ab2b3281-b8b8-4ae4-a68d-6c59391df8bc.png)
  
  
 ![Screen Shot 2021-11-29 at 10 24 15 PM](https://user-images.githubusercontent.com/35964921/143986112-d4bdb2fe-3c19-4b18-b276-dc6395bdb26e.png)

With a single click, all shadows become red. 

This single line in the shader allowed this to happen.

  <img width="502" alt="Screen Shot 2021-11-29 at 11 34 31 PM" src="https://user-images.githubusercontent.com/35964921/143986205-456ccf39-e75d-4223-83ee-4ebe7167c339.png">



 ## Rendering Setting.
 

https://user-images.githubusercontent.com/35964921/143986360-f639f27d-10cc-417b-9dbb-603eb2dc403f.mp4


After Selecting an object, I pressed between P and F for changing the object render.


## Rotation.



https://user-images.githubusercontent.com/35964921/143986566-11130816-1840-4bad-a81b-b9bf73dfe3ef.mp4



For each object, I had a angle x and angle y associated with it. So every time I render it, it would use the x and y adjustment.

  

 
  
## Light rotation.

https://user-images.githubusercontent.com/35964921/143986879-63d60ddf-144e-485c-9e61-86eebcc55d8a.mp4

`timee += 0.2;
				lightPos.x += sin(timee) * 0.5;
				lightPos.z += cos(timee) * 0.5;`
        
 This was used to allow light position to rotate in a circle. The time is a global variable that always increased.


 ## Perspective Camera.


https://user-images.githubusercontent.com/35964921/143987070-8fe13297-9b8e-45fd-9af6-de4e16103a12.mp4


We can manipulate the perspective camera of the world and the plane seperatly.


