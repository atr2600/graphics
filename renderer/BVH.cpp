//
// Created by khan on 4/6/19.
//

//#include <algorithm>
#include <algorithm>
#include "BVH.h"

BVH::BVH(Shape *s) {

    sivelab::Vector3D min, max;
    min = s->getMax();
    max = s->getMax();
    xdim[0] = min[0];
    xdim[2] = max[0];
    xdim[1] = (max[0]+min[0]/2);
    ydim[0] = min[1];
    ydim[2] = max[1];
    ydim[1] = (max[1]+min[1]/2);
    zdim[0] = min[2];
    zdim[2] = max[2];
    zdim[1] = (max[2]+min[2]/2);
    isthisabox=false;
    leftChild = s;
    rightChild = nullptr;


}

BVH::BVH(std::vector<Shape *> BVHs, int h) {
    //Check size for 1 or 2
    // Then you can just set the child to left and right
    // this is the osrt section

    //xsort 0
    //ysort 1
    //zsort 2
    isthisabox=true;

    if(h == 0) std::sort(BVHs.begin(),BVHs.end());
    if(h == 1) std::sort(BVHs.begin(),BVHs.end());
    if(h == 2) std::sort(BVHs.begin(),BVHs.end());


    if(BVHs.size()!=1){
        std::vector<Shape *> leftB(BVHs.begin(),BVHs.begin()+BVHs.size()/2);
        std::vector<Shape*> rightB(BVHs.begin()+BVHs.size()/2,BVHs.end());

        leftChild = new BVH(leftB,h+1);
        rightChild = new BVH(rightB,h+1);
        setValues((leftChild),leftB);
        setValues((rightChild),rightB);
        
    } else {
      leftChild = new BVH(BVHs[0]);
      rightChild = nullptr;
    }



}

void BVH::setValues(Shape* child, std::vector<Shape*> tree) {
    //set min mid max variables
    //lowest low and highest max of left and right child.
    child->setXdim(sivelab::Vector3D(tree[0]->getXdim()));
    child->setYdim(sivelab::Vector3D(tree[0]->getYdim()));
    child->setZdim(sivelab::Vector3D(tree[0]->getZdim()));
    for(int i = 0; i<tree.size();i++){
        if(getXdim()[0]>tree[i]->getXdim()[0]){
            child->xdim[0] = getXdim()[0];
        }
        if(getXdim()[2]<tree[i]->getXdim()[2]){
            child->xdim[2] = getXdim()[2];
        }
        if(getYdim()[0]>tree[i]->getYdim()[0]){
            child->xdim[0] = getYdim()[0];
        }
        if(getYdim()[2]<tree[i]->getYdim()[2]){
            child->xdim[2] = getYdim()[2];
        }
        if(getZdim()[0]>tree[i]->getZdim()[0]){
            child->xdim[0] = getZdim()[0];
        }
        if(getZdim()[2]<tree[i]->getZdim()[2]){
            child->xdim[2] = getZdim()[2];
        }
    }
    child->xdim[1] = child->xdim[2]-child->xdim[0];
    child->ydim[1] = child->ydim[2]-child->ydim[0];
    child->zdim[1] = child->zdim[2]-child->zdim[0];
}

bool BVH::intersect(double tmin, double &tmax, HitStruct &hit, Ray r) {
    double  txmin, txmax, tymin, tymax, tzmin, tzmax, txymin, txymax, txyzmax, txyzmin;

    double tHit, tNear;

    if(r.getDirection()[0] >= 0){
        txmin = (xdim[0]-r.getOrigin()[0])/r.getDirection()[0];
        txmax = (xdim[2]-r.getOrigin()[0])/r.getDirection()[0];
    } else {
        txmin = (xdim[2]-r.getOrigin()[0])/r.getDirection()[0];
        txmax = (xdim[0]-r.getOrigin()[0])/r.getDirection()[0];
    }
    if(r.getDirection()[1] >= 0){
        tymin = (ydim[0]-r.getOrigin()[1])/r.getDirection()[1];
        tymax = (ydim[2]-r.getOrigin()[1])/r.getDirection()[1];
    } else {
        tymin = (ydim[2]-r.getOrigin()[1])/r.getDirection()[1];
        tymax = (ydim[0]-r.getOrigin()[1])/r.getDirection()[1];
    }

    txymin = (txmin > tymin ? txmin:tymin);
    txymax = (txmax < tymax ? txmax:tymax);
    
    if(r.getDirection()[2] >= 0){
        tzmin = (zdim[0]-r.getOrigin()[2])/r.getDirection()[2];
        tzmax = (zdim[2]-r.getOrigin()[2])/r.getDirection()[2];
    } else {
        tzmin = (zdim[2]-r.getOrigin()[2])/r.getDirection()[2];
        tzmax = (zdim[0]-r.getOrigin()[2])/r.getDirection()[2];
    }

    if(tymax < tymin){
        return false;
    }


    if(txymax < txymin){
        return false;
    }
    txyzmin = (txymin > tzmin ? txymin:tzmin);
    txyzmax = (txymax < tzmax ? txymax:tzmax);
    if(txyzmin>txyzmax){
        return false;
    }

    bool ifHit = leftChild->intersect(tmin, tmax, hit, r);

    if(rightChild != nullptr){
        ifHit = ifHit || rightChild->intersect(tmin,tmax, hit, r);
    }

    if(ifHit && !isthisabox){
        returnName = leftChild->getColor();
        returnTvalue = leftChild->getTvalue();
    }
    return ifHit;

}



