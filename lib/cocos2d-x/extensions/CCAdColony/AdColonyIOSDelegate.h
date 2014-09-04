#import <AdColony/AdColony.h>
#import "CCAdColony.h"

@interface AdColonyIOSDelegate:NSObject<AdColonyDelegate, AdColonyAdDelegate>
{
    CCAdColonyObserver *observer_;
}
-(void) registerObserver:(CCAdColonyObserver *)observer;
@end