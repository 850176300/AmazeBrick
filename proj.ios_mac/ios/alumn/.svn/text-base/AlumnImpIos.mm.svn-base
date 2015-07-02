//
//  AlumnImpIos.cpp
//  Doctor2
//
//  Created by tanshoumei on 13-9-18.
//
//

#import "AlumnImpIos.h"

static AlumnImpIos* _alumnImpIos = nil;

@implementation AlumnImpIos
+ (AlumnImpIos*)shared
{
    if(!_alumnImpIos)
       _alumnImpIos = [[AlumnImpIos alloc] init];
    return _alumnImpIos;
}

+ (void)purge
{
    if(_alumnImpIos)
        [_alumnImpIos release];
}

- (void)saveToAlumn:(UIImage *)apImg
{
    if(false == isTakingPhoto) {
        
        isTakingPhoto = true;
        UIImageWriteToSavedPhotosAlbum(apImg, self, @selector(image:didFinishSavingWithError:contextInfo:), nil);
    }
}

//保存到本地回调
- (void)image:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo
{
	if (error != NULL)
	{
        if ([@"Data unavailable" isEqualToString:[error localizedDescription]]) {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"" message:@"This app does not have access to your photos.\nYou can enable access in Privacy Setting." delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
            [alert show];
            [alert release];
        }
        
	}else {
		UIAlertView *alert = [[[UIAlertView  alloc] initWithTitle:nil
							   message:@"Your image has been saved to Photos!"
                                                         delegate:nil
                                                cancelButtonTitle:nil
                                                otherButtonTitles:@"OK",nil] autorelease];
		[alert show];
	}
    
    isTakingPhoto = false;
}


@end