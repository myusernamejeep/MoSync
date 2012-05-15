/*
 Copyright (C) 2012 MoSync AB

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License,
 version 2, as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA 02110-1301, USA.
 */

/**
 * @file Test4.cpp
 * @author emma
 *
 * @brief Test case 4: Create new purchase object. Call getProductId and verify it.
 *
 */

#include "Test4.h"
#include "../wrapper/PurchaseManager.h"

namespace PurchaseTest
{
	/**
	 * Constructor.
	 * @param applicationController Will be notified when test's status
	 * changes.
	 */
	Test4::Test4(IApplicationController& applicationController):
		mApplicationController(applicationController)
	{
	}

	/**
	 * Destructor.
	 */
	Test4::~Test4()
	{
		mPurchase->removePurchaseListener(this);
	}

	/**
	 * Start the test.
	 */
	void Test4::startTest()
	{
		if ( getPlatform() == ANDROID )
		{
			mPurchase = new Purchase(ANDROID_PRODUCT_ID, this);
		}
		else if ( getPlatform() == IOS )
		{
			mPurchase = new Purchase(IOS_PRODUCT_ID, this);
		}
		mPurchase->addPurchaseListener(this);
	}

	/**
	 * Get the name of the test.
	 * @return Test's name.
	 */
	MAUtil::String Test4::getTestName() const
	{
		return "Test get the product If of a purchase";
	}

	/**
	 * Get the reason why the test failed.
	 * @return Reason why it failed.
	 */
	MAUtil::String Test4::getReason()
	{
		return "";
	}

	/**
	 * Notifies that the product has been validated by the App Store.
	 * NOTE: On Android there is no validation done at this step, if the
	 * product results to be unavailable, then the application will be later
	 * notified via a requestFailed() callback. The errorCode will equal
	 * #MA_PURCHASE_ERROR_INVALID_PRODUCT.
	 * Platform: iOS and Android.
	 * @param purchase The object that sent the event.
	 */
	void Test4::productValid(const Purchase& purchase)
	{
		if ( purchase.getHandle() == mPurchase->getHandle() )
		{
			if ( mPurchase->getProductId() == ANDROID_PRODUCT_ID ||
				mPurchase->getProductId() == IOS_PRODUCT_ID )
			{
				mApplicationController.testSucceeded(*this);
				MAUtil::String info = "Test4 succeeded";
				mApplicationController.log(info);
			}
			else
			{
				mApplicationController.testFailed(*this);
				MAUtil::String info = "Test4 failed, incorrect productId";
				mApplicationController.log(info);
			}
		}
	}

	/**
	 * Notifies that the product is not valid on the App Store.
	 * Platform: iOS.
	 * @param purchase The object that sent the event.
	 */
	void Test4::productInvalid(const Purchase& purchase)
	{
		if ( purchase.getHandle() == mPurchase->getHandle() )
		{
			mApplicationController.testFailed(*this);
			MAUtil::String info = "Test4 failed, product invalid";
			mApplicationController.log(info);
		}
	}

	/**
	 * Notifies that the transaction has been successfully processed.
	 * The user should receive the purchased product.
	 * Platform: Android and iOS.
	 * @param purchase The object that sent the event.
	 */
	void Test4::requestCompleted(const Purchase& purchase)
	{
	}

}
