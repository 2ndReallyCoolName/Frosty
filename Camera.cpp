
#include "Camera.h"

Camera::Camera()
{
	this->pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->posVector = XMLoadFloat3(&this->pos);
	this->rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->rotVector = XMLoadFloat3(&this->rot);
	updateViewMatrix();
}

void Camera::setProjectionMatrix(float fov_degrees, float ar, float nz, float fz)
{
	float fov_radians = XM_2PI * fov_degrees / 360.0f;
	this->projectionMatrix = XMMatrixPerspectiveFovLH(fov_radians, ar, nz, fz);
}

const XMMATRIX& Camera::getViewMatrix() const
{
	return this->viewMatrix;
}

const XMMATRIX& Camera::getProjectionMatrix() const
{
	return this->projectionMatrix;
}

const XMVECTOR& Camera::getPositionVector() const
{
	return this->posVector;
}

const XMFLOAT3& Camera::getPositionFloat3() const
{
	return this->pos;
}

const XMVECTOR& Camera::getRotationVector() const
{
	return this->rotVector;
}

const XMFLOAT3& Camera::getRotationFloat3() const
{
	return this->rot;
}

void Camera::setPosition(const XMVECTOR& pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = XMLoadFloat3(&this->pos);
	this->updateViewMatrix();
}

void Camera::setPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->updateViewMatrix();
}

void Camera::adjustPosition(const XMVECTOR& pos)
{
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->updateViewMatrix();
}

void Camera::adjustPosition(float x, float y, float z)
{
	this->pos.x += x; this->pos.y += y; this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->updateViewMatrix();
}

void Camera::setRotation(const XMVECTOR& rot)
{
	XMStoreFloat3(&this->rot, rot);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->updateViewMatrix();
}

void Camera::setRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->updateViewMatrix();
}

void Camera::adjustRotation(const XMVECTOR& rot)
{
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->updateViewMatrix();
}

void Camera::adjustRotation(float x, float y, float z)
{
	this->rot.x += x; this->rot.y += y; this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->updateViewMatrix();
}

void Camera::setLookAtPos(XMFLOAT3 lookAtPos)
{
	if (lookAtPos.x == this->pos.x && lookAtPos.y == this->pos.y && lookAtPos.z == this->pos.z) 
		return;

	lookAtPos.x = this->pos.x - lookAtPos.x;
	lookAtPos.y = this->pos.y - lookAtPos.y;
	lookAtPos.z = this->pos.z - lookAtPos.z;

	float pitch = 0.0f;
	if (lookAtPos.y != 0.0f) {
		const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
		pitch - atan(lookAtPos.y / distance);
	}

	float yaw = 0.0f;
	if (lookAtPos.x != 0.0f)
		yaw = atan(lookAtPos.x / lookAtPos.z);

	if (lookAtPos.z > 0) 
		yaw += XM_PI;
	
	this->setRotation(pitch, yaw, 0.0f);
}

const XMVECTOR& Camera::getForwardVector()
{
	return this->forward;
}

const XMVECTOR& Camera::getRightVector()
{
	return this->right;
}

const XMVECTOR& Camera::getLeftVector()
{
	return this->left;
}

const XMVECTOR& Camera::getBackwardVector()
{
	return this->backward;
}

void Camera::updateViewMatrix()
{
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
	XMVECTOR camTarget = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, camRotationMatrix);
	camTarget += this->posVector;
	XMVECTOR upDir = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, camRotationMatrix);
	this->viewMatrix = XMMatrixLookAtLH(this->posVector, camTarget, upDir);

	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	this->backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
	this->right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
	this->left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);

}
