#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

void ScreenLock::setTimerDisabled(bool disabled) {
    if (disabled)
        [[UIApplication sharedApplication] setIdleTimerDisabled: YES]
    else
        [[UIApplication sharedApplication] setIdleTimerDisabled: NO]
}
